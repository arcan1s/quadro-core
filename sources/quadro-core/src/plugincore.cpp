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


#include <QDebug>
#include <QDir>
#include <QSettings>
#include <QStandardPaths>

#include <quadro/quadro.h>
#include <pdebug/pdebug.h>

#include "version.h"


/**
 * @class PluginCore
 */
/**
 * @fn PluginCore
 */
PluginCore::PluginCore(QObject *parent, const bool debugCmd)
    : QObject(parent),
      debug(debugCmd)
{
}


/**
 * @fn ~PluginCore
 */
PluginCore::~PluginCore()
{
    if (debug) qDebug() << PDEBUG;
}


/**
 * @fn activePlugins
 */
QStringList PluginCore::activePlugins()
{
    if (debug) qDebug() << PDEBUG;

    QString fileName = QFileInfo(QDir(desktopPaths()[0]), QString("index.conf")).filePath();
    if (debug) qDebug() << PDEBUG << ":" << "Configuration file" << fileName;
    QSettings settings(fileName, QSettings::IniFormat);

    return settings.value(QString("Plugins")).toStringList();
}


/**
 * @fn desktopPaths
 */
QStringList PluginCore::desktopPaths()
{
    QStringList locations;
    locations.append(QString("%1/%2/%3").arg(QDir::homePath()).arg(HOME_PATH).arg(PLUGIN_PATH));

    QStringList defaultLocations = QStandardPaths::standardLocations(QStandardPaths::DataLocation);
    for (int i=0; i<defaultLocations.count(); i++)
        locations.append(QString("%1/%2/%3").arg(defaultLocations[i]).arg(SYSTEM_PATH).arg(PLUGIN_PATH));

    return locations;
}


/**
 * @fn plugins
 */
QMap<QString, PluginItem *> PluginCore::plugins()
{
    if (debug) qDebug() << PDEBUG;

    return m_plugins;
}


/**
 * @fn initPlugins
 */
void PluginCore::initPlugins()
{
    if (debug) qDebug() << PDEBUG;

    // start cleanup
    m_plugins.clear();

    m_plugins = getPlugins();
}


/**
 * @fn runPlugins
 */
void PluginCore::runPlugins(const QStringList _plugins)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Plugins" << _plugins;

    for (int i=0; i<_plugins.count(); i++) {
        if (!m_plugins.contains(_plugins[i])) {
            if (debug) qDebug() << PDEBUG << ":" << "Could not find plugin" << _plugins[i];
            continue;
        }
    }
}


/**
 * @fn saveActivePlugins
 */
void PluginCore::saveActivePlugins(const QStringList _plugins)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Plugins" << _plugins;

    QString fileName = QFileInfo(QDir(desktopPaths()[0]), QString("index.conf")).filePath();
    if (debug) qDebug() << PDEBUG << ":" << "Configuration file" << fileName;
    QSettings settings(fileName, QSettings::IniFormat);

    settings.setValue(QString("Plugins"), _plugins);

    settings.sync();
}


/**
 * @fn getPlugins
 */
QMap<QString, PluginItem *> PluginCore::getPlugins()
{
    if (debug) qDebug() << PDEBUG;

    QStringList filter("*.desktop");
    QStringList locations = desktopPaths();
    if (debug) qDebug() << PDEBUG << ":" << "Paths" << locations;
    QMap<QString, PluginItem *> items;

    for (int i=locations.count()-1; i>=0; i--) {
        QStringList entries = QDir(locations[i]).entryList(filter, QDir::Files);
        for (int j=0; j<entries.count(); j++) {
            QString desktop = QFileInfo(QDir(locations[i]), entries[j]).filePath();
            if (debug) qDebug() << PDEBUG << ":" << "Desktop" << desktop;
            PluginItem *item = new PluginItem(this, debug);
            item->readDesktop(desktop);
            items[desktop] = item;
        }
    }

    return items;
}
