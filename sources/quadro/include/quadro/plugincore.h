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
#include <QDir>
#include <QObject>
#include <QPluginLoader>

#include "config.h"
#include "quadrodebug.h"


class PluginItem;
class TabPluginItem;

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
     * @brief path to plugin desktop files
     * @return full paths to plugin desktop files
     */
    static QStringList desktopPaths();
    /**
     * @brief read plugin settings
     * @param _filePath      path to desktop file
     * @param _group         group for search
     * @return hash map with parameters
     */
    static QVariantHash pluginMetadata(const QString _filePath, const QString _group);
    // plugin methods
    /**
     * @brief find plugin
     * @param _plugin        plugin name
     * @return pointer to plugin or nullptr
     */
    PluginItem *plugin(const QString _plugin);
    /**
     * @brief find tab plugin
     * @param _plugin        plugin name
     * @return pointer to tab plugin or nullptr
     */
    TabPluginItem *tabPlugin(const QString _plugin);

public slots:
    /**
     * @brief init plugins from default paths
     */
    void initPlugins();

private:
    /**
     * @brief list of plugins
     */
    QHash<QString, PluginItem *> m_plugins;
    /**
     * @brief list of tab plugins
     */
    QHash<QString, TabPluginItem *> m_tabPlugins;
    /**
     * @brief create DBus session for specified plugin
     * @tparam T             plugin class depending on the type of plugin
     * @tparam Adaptor       DBus adaptor for the specified type of plugin
     * @param _name          plugin name
     * @param _plugin        pointer to plugin object
     */
    template<class T, class Adaptor> void createPluginDBusSession(const QString _name, T *_plugin)
    {
        qCDebug(LOG_LIB) << "Plugin name for DBus session" << _name;

        QDBusConnection bus = QDBusConnection::sessionBus();
        if (!bus.registerService(DBUS_PLUGIN_SERVICE)) {
            qCWarning(LOG_UI) << "Could not register service";
            qCWarning(LOG_UI) << bus.lastError().message();
        }
        if (!bus.registerObject(QString("/%1").arg(_name),
                                new Adaptor(this, _plugin),
                                QDBusConnection::ExportAllContents)) {
            qCWarning(LOG_UI) << "Could not register library object";
            qCWarning(LOG_UI) << bus.lastError().message();
        }
    };
    /**
     * @brief return plugins from default paths
     * @tparam T             plugin class depending on the type of plugin
     * @tparam Adaptor       DBus adaptor for the specified type of plugin
     * @param _group         plugin group in settings
     * @return map of generated plugin objects
     */
    template<class T, class Adaptor> QHash<QString, T *> getPlugins(const QString _group)
    {
        QStringList filter("*.desktop");
        QStringList locations = desktopPaths();
        qCInfo(LOG_LIB) << "Paths" << locations;
        QHash<QString, T *> items;

        foreach(const QString loc, locations) {
            QStringList entries = QDir(loc).entryList(filter, QDir::Files);
            foreach (const QString entry, entries) {
                QString fileName = QFileInfo(QDir(loc), entry).absoluteFilePath();
                qCInfo(LOG_LIB) << "Desktop" << fileName;
                // check settings
                QVariantHash metadata = pluginMetadata(fileName, _group);
                if (!metadata.contains(QString("Name")))
                    continue;
                // init
                QString name = metadata[QString("Name")].toString();
                QString libraryName = QString("%1/lib%2.so").arg(loc).arg(name);
                QPluginLoader loader(libraryName, this);
                qCInfo(LOG_LIB) << "Loading" << libraryName;
                // load plugin
                QObject *plugin = loader.instance();
                if (loader.isLoaded()) {
                    T *item = qobject_cast<T *>(plugin);
                    if (!item) {
                        qCCritical(LOG_LIB) << "Could not cast plugin";
                        continue;
                    }
                    items[name] = item;
                    createPluginDBusSession<T, Adaptor>(name, item);
                } else {
                    qCCritical(LOG_LIB) << "Could not load the library for" << name;
                    qCCritical(LOG_LIB) << "Error" << loader.errorString();
                    continue;
                }
            }
        }

        return items;
    };
};


#endif /* PLUGINCORE_H */
