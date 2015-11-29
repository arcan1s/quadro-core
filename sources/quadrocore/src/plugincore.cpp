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
    for (auto name : m_plugins.keys() + m_tabPlugins.keys())
        QDBusConnection::sessionBus().unregisterObject(QString("/%1").arg(name));
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
void PluginCore::loadPlugin(const QString _plugin)
{
    qCDebug(LOG_LIB) << "Loading plugin" << _plugin;

    if (m_plugins.contains(_plugin)) {
        m_plugins[_plugin]->init();
        m_loadedPlugins.append(_plugin);
    } else if (m_tabPlugins.contains(_plugin)) {
        m_tabPlugins[_plugin]->init();
        m_loadedPlugins.append(_plugin);
    } else {
        qCWarning(LOG_LIB) << "Could not load" << _plugin << "because it was not found";
    }
}


/**
 * @fn pluginMetadata
 */
QVariantHash PluginCore::pluginMetadata(const QString _filePath, const QString _group)
{
    qCDebug(LOG_LIB) << "File path" << _filePath;

    QVariantHash pluginData;
    QSettings settings(_filePath, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    if (!settings.childGroups().contains(_group))
        return pluginData;

    settings.beginGroup(_group);
    pluginData[QString("Comment")] = settings.value(QString("Comment"), QString(""));
    pluginData[QString("Name")] = settings.value(QString("Name"), QString("none"));
    settings.endGroup();

    return pluginData;
}


/**
 * @fn unloadPlugin
 */
void PluginCore::unloadPlugin(const QString _plugin, const QString _configPath)
{
    qCDebug(LOG_LIB) << "Disabling plugin" << _plugin << "with configuration" << _configPath;

    if (m_plugins.contains(_plugin)) {
        m_plugins[_plugin]->quit(_configPath);
        m_loadedPlugins.removeAll(_plugin);
    } else if (m_tabPlugins.contains(_plugin)) {
        m_tabPlugins[_plugin]->quit(_configPath);
        m_loadedPlugins.removeAll(_plugin);
    } else {
        qCWarning(LOG_LIB) << "Could not disable" << _plugin << "because it was not found";
    }
}


/**
 * @fn plugin
 */
PluginInterface *PluginCore::plugin(const QString _plugin)
{
    qCDebug(LOG_LIB) << "Plugin name" << _plugin;

    return m_plugins.value(_plugin, nullptr);
}


/**
 * @fn tabPlugin
 */
TabPluginInterface *PluginCore::tabPlugin(const QString _plugin)
{
    qCDebug(LOG_LIB) << "Plugin name" << _plugin;

    return m_tabPlugins.value(_plugin, nullptr);
}


/**
 * @fn initPlugins
 */
void PluginCore::initPlugins()
{
    // start cleanup
    m_plugins.clear();
    m_tabPlugins.clear();

    m_plugins = getPlugins<PluginInterface, PluginAdaptor>(QString("Quadro plugin"));
    m_tabPlugins = getPlugins<TabPluginInterface, TabPluginAdaptor>(QString("Quadro tabplugin"));
}
