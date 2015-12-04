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
 * @file plugin.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */

#include "quadrocore/quadro.h"

#include <QDir>
#include <QSettings>
#include <QStandardPaths>


/**
 * @class PluginCore
 */
/**
 * @fn PluginCore
 */
PluginCore::PluginCore(QObject *parent)
    : QObject(parent)
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;
}


/**
 * @fn ~PluginCore
 */
PluginCore::~PluginCore()
{
    QDBusConnection::sessionBus().unregisterService(DBUS_PLUGIN_SERVICE);

    m_plugins.clear();
    m_tabPlugins.clear();
}


/**
 * @fn configurationPath
 */
QString PluginCore::configurationPath(const QString _fileName)
{
    qCDebug(LOG_LIB) << "Looking for" << _fileName;

    QString root = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);

    return QString("%1/%2/%3/%4").arg(root).arg(HOME_PATH).arg(PLUGIN_PATH).arg(_fileName);
}


/**
 * @fn desktopPaths
 */
QStringList PluginCore::desktopPaths()
{
    QStringList locations;
    QStringList defaultLocations = QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation);
    for (auto loc : defaultLocations)
        locations.append(QString("%1/%2/%3").arg(loc).arg(HOME_PATH).arg(PLUGIN_PATH));

    return locations;
}


/**
 * @fn loadPlugin
 */
int PluginCore::loadPlugin(const QString _plugin)
{
    qCDebug(LOG_LIB) << "Loading plugin" << _plugin;

    int index = -1;
    if (!m_allPlugins.contains(_plugin)) {
        qCWarning(LOG_LIB) << "Could not load" << _plugin << "because it was not found";
        return index;
    }

    QString type = m_allPlugins[_plugin].toHash()[QString("Group")].toString();
    QString location = m_allPlugins[_plugin].toHash()[QString("Location")].toString();
    if (type == QString("plugin")) {
        PluginInterface *item = createPlugin<PluginInterface>(_plugin, location);
        if (item == nullptr)
            return index;
        // get possible index
        index = m_plugins.count();
        while (m_plugins.contains(index))
            index++;
        // add item to index and create interface
        m_plugins[index] = item;
        createPluginDBusSession<PluginInterface, PluginAdaptor>(_plugin, index, item);
    } else if (type == QString("tabplugin")) {
        TabPluginInterface *item = createPlugin<TabPluginInterface>(_plugin, location);
        if (item == nullptr)
            return index;
        // get possible index
        index = m_tabPlugins.count();
        while (m_tabPlugins.contains(index))
            index++;
        // add item to index and create interface
        m_tabPlugins[index] = item;
        createPluginDBusSession<TabPluginInterface, TabPluginAdaptor>(_plugin, index, item);
    } else {
        qCWarning(LOG_LIB) << "Invalid plugin type" << type;
    }

    return index;
}


/**
 * @fn pluginMetadata
 */
QVariantHash PluginCore::pluginMetadata(const QString _filePath)
{
    qCDebug(LOG_LIB) << "File path" << _filePath;

    QVariantHash pluginData;
    QSettings settings(_filePath, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    QString group;
    QString configGroup;
    if (settings.childGroups().contains(QString("Quadro plugin"))) {
        group = QString("plugin");
        configGroup = QString("Quadro plugin");
    } else if (settings.childGroups().contains(QString("Quadro tabplugin"))) {
        group = QString("tabplugin");
        configGroup = QString("Quadro tabplugin");
    } else {
        return pluginData;
    }

    settings.beginGroup(configGroup);
    pluginData[QString("Comment")] = settings.value(QString("Comment"), QString(""));
    pluginData[QString("Name")] = settings.value(QString("Name"), QString("none"));
    pluginData[QString("Group")] = group;
    pluginData[QString("Location")] = QFileInfo(_filePath).absolutePath();
    settings.endGroup();

    return pluginData;
}


/**
 * @fn unloadPlugin
 */
bool PluginCore::unloadPlugin(const QString _plugin, const int _index, const QString _configPath)
{
    qCDebug(LOG_LIB) << "Disabling plugin" << _plugin << "with index" << _index
                     << "using configuration" << _configPath;

    QString type = m_allPlugins[_plugin].toHash()[QString("Group")].toString();
    if (type == QString("plugin")) {
        if (!m_plugins.contains(_index)) {
            qCWarning(LOG_LIB) << "Invalid index" << _index;
            return false;
        }
        // send quit signal to plugin
        m_plugins[_index]->quit(_configPath);
        // delete interface
        QDBusConnection::sessionBus().unregisterObject(QString("/%1/%2").arg(_plugin).arg(_index));
        // remove from index
        m_plugins.remove(_index);
    } else if (type == QString("tabplugin")) {
        if (!m_tabPlugins.contains(_index)) {
            qCWarning(LOG_LIB) << "Invalid index" << _index;
            return false;
        }
        // send quit signal to plugin
        m_tabPlugins[_index]->quit(_configPath);
        // delete interface
        QDBusConnection::sessionBus().unregisterObject(QString("/%1/%2").arg(_plugin).arg(_index));
        // remove from index
        m_tabPlugins.remove(_index);
    } else {
        qCWarning(LOG_LIB) << "Invalid plugin type" << type;
        return false;
    }

    return true;
}


/**
 * @fn plugin
 */
PluginInterface *PluginCore::plugin(const int _index)
{
    qCDebug(LOG_LIB) << "Plugin index" << _index;

    if (!m_plugins.contains(_index)) {
        qCWarning(LOG_LIB) << "Invalid index" << _index;
        return nullptr;
    }

    return m_plugins[_index];
}


/**
 * @fn tabPlugin
 */
TabPluginInterface *PluginCore::tabPlugin(const int _index)
{
    qCDebug(LOG_LIB) << "Plugin index" << _index;

    if (!m_tabPlugins.contains(_index)) {
        qCWarning(LOG_LIB) << "Invalid index" << _index;
        return nullptr;
    }

    return m_tabPlugins[_index];
}


/**
 * @fn initPlugins
 */
void PluginCore::initPlugins()
{
    // start cleanup
    m_allPlugins.clear();
    m_plugins.clear();
    m_tabPlugins.clear();

    QStringList filter("*.desktop");
    QStringList locations = desktopPaths();
    qCInfo(LOG_LIB) << "Paths" << locations;

    for (auto loc : locations) {
        QStringList entries = QDir(loc).entryList(filter, QDir::Files);
        for (auto entry : entries) {
            QString fileName = QFileInfo(QDir(loc), entry).absoluteFilePath();
            qCInfo(LOG_LIB) << "Desktop" << fileName;
            // check settings
            QVariantHash metadata = pluginMetadata(fileName);
            if (!metadata.contains(QString("Name")))
                continue;
            m_allPlugins[metadata[QString("Name")].toString()] = metadata;
        }
    }
}
