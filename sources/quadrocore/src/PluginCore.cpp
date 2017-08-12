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
 * @file PluginCore.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadrocore/Quadro.h"

#include <QDir>
#include <QStandardPaths>

using namespace Quadro;


/**
 * @class PluginCore
 */
/**
 * @fn PluginCore
 */
PluginCore::PluginCore(QuadroCore *_parent)
    : QObject(_parent)
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;
}


/**
 * @fn ~PluginCore
 */
PluginCore::~PluginCore()
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;

    QDBusConnection::sessionBus().unregisterService(DBUS_PLUGIN_SERVICE);

    m_allPlugins.clear();
    m_plugins.clear();
}


/**
 * @fn configurationPath
 */
QString PluginCore::configurationPath(const QString &_fileName)
{
    qCDebug(LOG_LIB) << "Looking for" << _fileName;

    QString root
        = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);

    return QString("%1/%2/%3/%4")
        .arg(root)
        .arg(HOME_PATH)
        .arg(PLUGIN_PATH)
        .arg(_fileName);
}


/**
 * @fn desktopPaths
 */
QStringList PluginCore::desktopPaths()
{
    QStringList locations;
    QStringList defaultLocations = QStandardPaths::standardLocations(
        QStandardPaths::GenericDataLocation);
    for (auto &loc : defaultLocations)
        locations.append(
            QString("%1/%2/%3").arg(loc).arg(HOME_PATH).arg(PLUGIN_PATH));

    return locations;
}


/**
 * @fn initPlugin
 */
void PluginCore::initPlugin(const int _index, const QString &_configPath)
{
    qCDebug(LOG_LIB) << "Init plugin" << _index << "using file" << _configPath;

    m_plugins[_index]->setArgs(static_cast<QuadroCore *>(parent()));
    m_plugins[_index]->readSettings(configurationPath(_configPath));

    return m_plugins[_index]->init();
}


/**
 * @fn knownPlugins
 */
QHash<QString, PluginRepresentation *>
PluginCore::knownPlugins(const QString &_group) const
{
    qCDebug(LOG_LIB) << "Requested type is" << _group;

    QHash<QString, PluginRepresentation *> foundPlugins;
    for (auto plugin : m_allPlugins.values()) {
        if ((!_group.isEmpty()) && (plugin->group() != _group))
            continue;
        foundPlugins[plugin->name()] = plugin;
    }

    return foundPlugins;
}


/**
 * @fn loadPlugin
 */
int PluginCore::loadPlugin(const QString &_plugin)
{
    qCDebug(LOG_LIB) << "Loading plugin" << _plugin;

    int index = -1;
    if (!m_allPlugins.contains(_plugin)) {
        qCWarning(LOG_LIB) << "Could not load" << _plugin
                           << "because it was not found";
        return index;
    }

    QString type = m_allPlugins[_plugin]->group();
    QString location = m_allPlugins[_plugin]->location();
    if (type == "plugin")
        index
            = registerPlugin<PluginInterface, PluginAdaptor>(_plugin, location);
    else if (type == "tabplugin")
        index = registerPlugin<TabPluginInterface, TabPluginAdaptor>(_plugin,
                                                                     location);
    else if (type == "genericplugin")
        index = registerPlugin<QuadroPluginInterface, QuadroPluginAdaptor>(
            _plugin, location);
    else
        qCWarning(LOG_LIB) << "Invalid plugin type" << type;

    return index;
}


/**
 * @fn unloadPlugin
 */
bool PluginCore::unloadPlugin(const int _index, const QString &_configPath)
{
    qCDebug(LOG_LIB) << "Disabling plugin with index" << _index
                     << "using configuration" << _configPath;

    if (!m_plugins.contains(_index)) {
        qCWarning(LOG_LIB) << "Invalid index" << _index;
        return false;
    }
    // send quit signal to plugin
    m_plugins[_index]->quit(configurationPath(_configPath));
    // remove from index
    auto plugin = m_plugins.take(_index);
    delete plugin;

    return true;
}


/**
 * @fn initPlugins
 */
void PluginCore::initPlugins()
{
    // start cleanup
    m_allPlugins.clear();
    m_plugins.clear();

    QStringList filter("*.desktop");
    QStringList locations = desktopPaths();
    qCInfo(LOG_LIB) << "Paths" << locations;

    for (auto &loc : locations) {
        QStringList entries = QDir(loc).entryList(filter, QDir::Files);
        for (auto &entry : entries) {
            QString fileName = QFileInfo(QDir(loc), entry).absoluteFilePath();
            qCInfo(LOG_LIB) << "Desktop" << fileName;
            // check settings
            auto repr = PluginRepresentation::fromFile(fileName);
            if ((!repr) || (m_allPlugins.contains(repr->name())))
                continue;
            m_allPlugins[repr->name()] = repr;
        }
    }
}


/**
 * @fn generateIndex
 */
int PluginCore::generateIndex(QuadroPluginInterface *_plugin)
{
    int index = 0;
    while (m_plugins.contains(index))
        index++;
    qCInfo(LOG_LIB) << "Found index" << index;
    m_plugins[index] = _plugin;

    return index;
}
