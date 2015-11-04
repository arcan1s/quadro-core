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
    m_tabPlugins.clear();
}


/**
 * @fn desktopPaths
 */
QStringList PluginCore::desktopPaths()
{
    QStringList locations;
    QStringList defaultLocations = QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation);
    foreach (const QString loc, defaultLocations)
        locations.append(QString("%1/%2/%3").arg(loc).arg(HOME_PATH).arg(PLUGIN_PATH));

    return locations;
}


/**
 * @fn plugin
 */
PluginItem *PluginCore::plugin(const QString _plugin)
{
    qCDebug(LOG_LIB) << "Plugin name" << _plugin;

    return m_plugins.value(_plugin, nullptr);
}


/**
 * @fn tabPlugin
 */
TabPluginItem *PluginCore::tabPlugin(const QString _plugin)
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

    m_plugins = getPlugins();
    m_tabPlugins = getTabPlugins();
}


/**
 * @fn getPlugins
 */
QHash<QString, PluginItem *> PluginCore::getPlugins()
{
    QStringList filter("*.desktop");
    QStringList locations = desktopPaths();
    qCInfo(LOG_LIB) << "Paths" << locations;
    QHash<QString, PluginItem *> items;

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


/**
 * @fn getTabPlugins
 */
QHash<QString, TabPluginItem *> PluginCore::getTabPlugins()
{
    QStringList filter("*.desktop");
    QStringList locations = desktopPaths();
    qCInfo(LOG_LIB) << "Paths" << locations;
    QHash<QString, TabPluginItem *> items;

    foreach(const QString loc, locations) {
        QStringList entries = QDir(loc).entryList(filter, QDir::Files);
        foreach (const QString entry, entries) {
            QString fileName = QFileInfo(QDir(loc), entry).absoluteFilePath();
            qCInfo(LOG_LIB) << "Desktop" << fileName;
            // check settings
            QVariantHash metadata = TabPluginItem::readDesktop(fileName);
            if (!metadata.contains(QString("Name")))
                continue;
            // init
            QString name = metadata[QString("Name")].toString();
            QString libraryName = QString("%1/lib%2.so").arg(loc).arg(name);
            QPluginLoader loader(libraryName, this);
            // load plugin
            QObject *plugin = loader.instance();
            if (plugin) {
                qCInfo(LOG_LIB) << "Loading" << libraryName;
                try {
                    items[name] = dynamic_cast<TabPluginItem *>(plugin);
                } catch (std::bad_cast &e) {
                    qCCritical(LOG_LIB) << "Could not cast" << name << e.what();
                    continue;
                }
                items[name]->setApi(metadata[QString("API")].toInt());
                items[name]->setComment(metadata[QString("Comment")].toString());
                items[name]->setName(metadata[QString("Name")].toString());
            } else {
                qCWarning(LOG_LIB) << "Could not load the library for" << name;
                qCWarning(LOG_LIB) << "Error" << loader.errorString();
                continue;
            }
        }
    }

    return items;
}
