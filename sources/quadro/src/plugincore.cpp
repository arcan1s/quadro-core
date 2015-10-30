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


#include "quadro/quadro.h"

#include <QDir>
#include <QPluginLoader>
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
    m_plugins.clear();
}


/**
 * @fn activePlugins
 */
QStringList PluginCore::activePlugins()
{
    QString fileName = QFileInfo(QDir(desktopPaths()[0]), QString("index.conf")).filePath();
    qCInfo(LOG_LIB) << "Configuration file" << fileName;
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");

    return settings.value(QString("Plugins")).toStringList();
}


/**
 * @fn desktopPaths
 */
QStringList PluginCore::desktopPaths()
{
    QStringList locations;
    QStringList defaultLocations = QStandardPaths::standardLocations(QStandardPaths::DataLocation);
    for (int i=0; i<defaultLocations.count(); i++)
        locations.append(QString("%1/%2/%3").arg(defaultLocations[i]).arg(HOME_PATH).arg(PLUGIN_PATH));

    return locations;
}


/**
 * @fn plugins
 */
QMap<QString, PluginItem *> PluginCore::plugins()
{
    return m_plugins;
}


/**
 * @fn initPlugins
 */
void PluginCore::initPlugins()
{
    // start cleanup
    m_plugins.clear();

    m_plugins = getPlugins();
}


/**
 * @fn runPlugins
 */
void PluginCore::runPlugins(const QStringList _plugins)
{
    qCDebug(LOG_LIB) << "Plugins" << _plugins;

    for (int i=0; i<_plugins.count(); i++) {
        if (!m_plugins.contains(_plugins[i])) {
            qCWarning(LOG_LIB) << "Could not find plugin" << _plugins[i];
            continue;
        }
        m_plugins[_plugins[i]]->createSession();
        m_plugins[_plugins[i]]->startTimer();
    }
}


/**
 * @fn saveActivePlugins
 */
void PluginCore::saveActivePlugins(const QStringList _plugins)
{
    qCDebug(LOG_LIB) << "Plugins" << _plugins;

    QString fileName = QFileInfo(QDir(desktopPaths()[0]), QString("index.conf")).filePath();
    qCInfo(LOG_LIB) << "Configuration file" << fileName;
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");

    settings.setValue(QString("Plugins"), _plugins);

    settings.sync();
}


/**
 * @fn stopPlugin
 */
void PluginCore::stopPlugin(const QString _plugin)
{
    qCDebug(LOG_LIB) << "Plugin" << _plugin;
    if (!m_plugins.contains(_plugin)) {
        qCWarning(LOG_LIB) << "Could not find plugin" << _plugin;
        return;
    }

    m_plugins[_plugin]->stopTimer();
    m_plugins[_plugin]->removeSession();
}


/**
 * @fn getPlugins
 */
QMap<QString, PluginItem *> PluginCore::getPlugins()
{
    QStringList filter("*.desktop");
    QStringList locations = desktopPaths();
    qCInfo(LOG_LIB) << "Paths" << locations;
    QMap<QString, PluginItem *> items;

    foreach(const QString loc, locations) {
        QStringList entries = QDir(loc).entryList(filter, QDir::Files);
        for (int j=0; j<entries.count(); j++) {
            QString desktop = QFileInfo(QDir(loc), entries[j]).filePath();
            qCInfo(LOG_LIB) << "Desktop" << desktop;
            // generate path
            QString libraryName = QString("lib%1").arg(entries[j]);
            libraryName.replace(QString(".desktop"), QString(".so"));
            QPluginLoader loader(libraryName);
            // load plugin
            QObject *plugin = loader.instance();
            if (plugin) {
                qCInfo(LOG_LIB) << "Loading" << libraryName;
                items[desktop] = dynamic_cast<PluginItem *>(plugin);
            } else {
                qCWarning(LOG_LIB) << "Could not load the library for" << desktop;
                qCWarning(LOG_LIB) << "Error" << loader.errorString();
                continue;
            }
        }
    }

    return items;
}
