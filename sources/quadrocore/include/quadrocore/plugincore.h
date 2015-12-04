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

#include <QDBusConnection>
#include <QDBusMessage>
#include <QObject>
#include <QPluginLoader>

#include "config.h"
#include "quadrodebug.h"


class PluginInterface;
class TabPluginInterface;

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
    explicit PluginCore(QObject *parent);
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
     * @brief load plugin by name
     * @param _plugin        plugin name
     * @return unique index of loaded plugin or -1 if no plugin has been loaded
     */
    int loadPlugin(const QString _plugin);
    /**
     * @brief read plugin settings
     * @param _filePath      path to desktop file
     * @return hash map with parameters
     */
    static QVariantHash pluginMetadata(const QString _filePath);
    /**
     * @brief unload plugin. This method calls Interface::quit() method and remove
     * the plugin from loaded list
     * @param _plugin        plugin name
     * @param _index         plugin index
     * @param _configPath    full path to configuration file
     * @return status of plugin unloading
     */
    bool unloadPlugin(const QString _plugin, const int _index, const QString _configPath);
    // plugin methods
    /**
     * @brief find plugin
     * @param _index         plugin index
     * @return pointer to plugin or nullptr
     */
    PluginInterface *plugin(const int _index);
    /**
     * @brief find tab plugin
     * @param _index         plugin index
     * @return pointer to tab plugin or nullptr
     */
    TabPluginInterface *tabPlugin(const int _index);

public slots:
    /**
     * @brief init plugins from default paths
     */
    void initPlugins();

private:
    /**
     * @brief all available plugins with metadata
     */
    QVariantHash m_allPlugins;
    /**
     * @brief list of plugins
     */
    QHash<int, PluginInterface *> m_plugins;
    /**
     * @brief list of tab plugins
     */
    QHash<int, TabPluginInterface *> m_tabPlugins;
    /**
     * @brief init plugin from default paths
     * @tparam T             plugin class depending on the type of plugin
     * @param _name          plugin name
     * @param _location      plugin location
     * @return plugin objects
     */
    template<class T> T *createPlugin(const QString _name, const QString _location)
    {
        QString libraryName = QString("%1/lib%2.so").arg(_location).arg(_name);
        QPluginLoader loader(libraryName, this);
        qCInfo(LOG_LIB) << "Loading" << libraryName;
        // load plugin
        QObject *plugin = loader.instance();
        T *item = nullptr;
        if (loader.isLoaded()) {
            item = qobject_cast<T *>(plugin);
            if (!item) {
                qCCritical(LOG_LIB) << "Could not cast plugin";
            }
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
     * @param _name          plugin name
     * @param _index         plugin index
     * @param _plugin        pointer to plugin object
     */
    template<class T, class Adaptor> void createPluginDBusSession(const QString _name, const int _index,
                                                                  T *_plugin)
    {
        qCDebug(LOG_LIB) << "Plugin name for DBus session" << _name;

        QDBusConnection bus = QDBusConnection::sessionBus();
        if (!bus.registerService(DBUS_PLUGIN_SERVICE)) {
            qCWarning(LOG_LIB) << "Could not register service";
            qCWarning(LOG_LIB) << bus.lastError().message();
        }
        if (!bus.registerObject(QString("/%1/%2").arg(_name).arg(_index),
                                new Adaptor(this, _plugin),
                                QDBusConnection::ExportAllContents)) {
            qCWarning(LOG_LIB) << "Could not register library object";
            qCWarning(LOG_LIB) << bus.lastError().message();
        }
    };
};


#endif /* PLUGINCORE_H */
