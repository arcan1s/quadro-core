/***************************************************************************
 *   This file is part of quadro                                           *
 *                                                                         *
 *   quadro is free software: you can redistribute it and/or               *
 *   modify it under the terms of the GNU General Public License as        *
 *   published by the Free Software Foundation, either version 3 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   quadro is distributed in the hope that it will be useful,             *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with quadro. If not, see http://www.gnu.org/licenses/           *
 ***************************************************************************/
/**
 * @file plugincore.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef PLUGINCORE_H
#define PLUGINCORE_H

#include <QApplication>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QPluginLoader>
#include <QTranslator>

#include <typeinfo>

#include "config.h"
#include "quadrodebug.h"
#include "pluginrepresentation.h"


class PluginRepresentation;
class QuadroCore;
class QuadroPluginInterface;

/**
 * @brief The PluginCore class provides plugin backend
 */
class PluginCore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList desktopPaths READ desktopPaths)

public:
    /**
     * @brief PluginCore class constructor
     * @param parent         pointer to parent item
     */
    explicit PluginCore(QuadroCore *parent);
    /**
     * @brief PluginCore class destructor
     */
    virtual ~PluginCore();
    /**
     * @brief generate configuration path for given file name in the writable
     * locations. This method will return path even if the file does not exist
     * @return absolute path to configuration file
     */
    static QString configurationPath(const QString _fileName);
    /**
     * @brief path to plugin desktop files
     * @return full paths to plugin desktop files
     */
    static QStringList desktopPaths();
    /**
     * @brief pass parameter to plugin and init it
     * @param _index         plugin index
     * @param _configuration general configuration dictionary
     * @param _configPath    plugin specific configuration file name
     */
    void initPlugin(const int _index, const QVariantHash _configuration,
                    const QString _configPath);
    /**
     * @brief get list of all known plugins in their representations
     * @param _group         return only plugins with specified group
     * @return list of PluginRepresentation objects
     */
    QHash<QString, PluginRepresentation *> knownPlugins(const QString _group = QString()) const;
    /**
     * @brief load plugin by name
     * @param _plugin        plugin name
     * @return unique index of loaded plugin or -1 if no plugin has been loaded
     */
    int loadPlugin(const QString _plugin);
    /**
     * @brief unload plugin. This method calls Interface::quit() method and remove
     * the plugin from loaded list
     * @param _index         plugin index
     * @param _configPath    full path to configuration file
     * @return status of plugin unloading
     */
    bool unloadPlugin(const int _index, const QString _configPath);
    // plugin methods
    /**
     * @brief find initialized plugin by index
     * @tparam T             plugin class
     * @param _index         plugin index
     * @return pointer to plugin or nullptr in case if cast is not possible
     */
    template<class T> T *plugin(const int _index)
    {
        qCDebug(LOG_LIB) << "Plugin index" << _index;

        if (!m_plugins.contains(_index)) {
            qCWarning(LOG_LIB) << "Invalid index" << _index;
            return nullptr;
        }
        T *item = nullptr;
        try {
            item = dynamic_cast<T *>(m_plugins[_index]);
        } catch (std::bad_cast &bc) {
            qCWarning(LOG_LIB) << "Could not cast index" << _index <<
                               "to requested interface" << bc.what();
        }

        return item;
    };

public slots:
    /**
     * @brief init plugins from default paths
     */
    void initPlugins();

private:
    /**
     * @brief all available plugins with metadata
     */
    QHash<QString, PluginRepresentation *> m_allPlugins;
    /**
     * @brief list of plugins
     */
    QHash<int, QuadroPluginInterface *> m_plugins;
    /**
     * @brief init plugin from default paths
     * @tparam T             plugin class depending on the type of plugin
     * @param _name          plugin name
     * @param _location      plugin location
     * @return plugin objects
     */
    template<class T> T *createPlugin(const QString _name, const QString _location)
    {
        qCDebug(LOG_LIB) << "Create plugin" << _name << "from" << _location;

        QString libraryName = QString("%1/lib%2.so").arg(_location).arg(_name);
        QPluginLoader loader(libraryName, this);
        qCInfo(LOG_LIB) << "Loading" << libraryName;
        // load plugin
        QObject *plugin = loader.instance();
        T *item = nullptr;
        if (loader.isLoaded()) {
            item = qobject_cast<T *>(plugin)->createInstance();
            if (!item)
                qCCritical(LOG_LIB) << "Could not cast plugin";
        } else {
            qCCritical(LOG_LIB) << "Could not load the library for" << _name;
            qCCritical(LOG_LIB) << "Error" << loader.errorString();
        }

        return item;
    };
    /**
     * @brief create DBus session for specified plugin
     * @tparam T             plugin class depending on the type of plugin
     * @tparam Adaptor       DBus adaptor for the specified type of plugin
     * @param _index         plugin index
     * @param _plugin        pointer to plugin object
     */
    template<class T, class Adaptor> void createPluginDBusSession(const int _index, T *_plugin)
    {
        qCDebug(LOG_LIB) << "Plugin name for DBus session" << _index;

        QDBusConnection bus = QDBusConnection::sessionBus();
        if (!bus.registerService(DBUS_PLUGIN_SERVICE)) {
            qCWarning(LOG_LIB) << "Could not register service";
            qCWarning(LOG_LIB) << bus.lastError().message();
        }
        if (!bus.registerObject(QString("/%1").arg(_index),
                                new Adaptor(this, _plugin),
                                QDBusConnection::ExportAllContents)) {
            qCWarning(LOG_LIB) << "Could not register library object";
            qCWarning(LOG_LIB) << bus.lastError().message();
        }
    };
    /**
     * @brief generate plugin index
     * @param _plugin        pointer to plugin item
     * @return generated plugin index
     */
    int generateIndex(QuadroPluginInterface *_plugin);
    /**
     * @brief create plugin, its dbus service and register it
     * @tparam T             plugin class depending on the type of plugin
     * @tparam Adaptor       DBus adaptor for the specified type of plugin
     * @param _name          plugin name
     * @param _location      plugin location
     * @return plugin registered index
     */
    template<class T, class Adaptor> int registerPlugin(const QString _name, const QString _location)
    {
        qCDebug(LOG_LIB) << "Register plugin" << _name << "from" << _location;

        // initialization
        int index = -1;
        T *item = createPlugin<T>(_name, _location);
        if (item == nullptr)
            return index;
        index = generateIndex(item);
        // main DBus session
        createPluginDBusSession<T, Adaptor>(index, item);
        // load plugin
        bool trStatus;
        static QTranslator pluginTranslator;
        trStatus = pluginTranslator.load(QString("core-quadro-%1_%2").arg(_name)
                                             .arg(QLocale::system().name()),
                                         QString("%1/%2/%3/%4").arg(ROOT_INSTALL_DIR)
                                             .arg(DATA_INSTALL_DIR).arg(HOME_PATH)
                                             .arg(TRANSLATION_PATH));
        qCDebug(LOG_LIB) << "Loading plugin" << _name << "specific translation" << trStatus;
        trStatus = qApp->installTranslator(&pluginTranslator);
        qCDebug(LOG_LIB) << "Install translator for" << _name << trStatus;

        return index;
    };
};


#endif /* PLUGINCORE_H */
