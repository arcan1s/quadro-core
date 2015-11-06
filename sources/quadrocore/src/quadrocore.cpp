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
 * @file quadrocore.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include <QDBusConnection>
#include <QDBusMessage>

#include "quadro/quadro.h"


/**
 * @class QuadroCore
 */
/**
 * @fn QuadroCore
 */
QuadroCore::QuadroCore(QObject *parent, const QVariantHash configuration)
    : QObject(parent)
    , m_configuration(configuration)
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;

    m_favorites = new FavoritesCore(this);
    m_favorites->initApplications();
    m_filemanager = new FileManagerCore(this);
    m_launcher = new LauncherCore(this);
    m_launcher->initApplications();
    m_plugin = new PluginCore(this);
    m_plugin->initPlugins();
    m_recently = new RecentlyCore(this, m_configuration[QString("RecentItemsCount")].toInt());
    m_recently->initApplications();

    createDBusSession();
}


/**
 * @fn ~QuadroCore
 */
QuadroCore::~QuadroCore()
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;

    QDBusConnection::sessionBus().unregisterObject(DBUS_OBJECT_PATH);
    QDBusConnection::sessionBus().unregisterService(DBUS_SERVICE);

    delete m_favorites;
    delete m_filemanager;
    delete m_launcher;
    delete m_plugin;
    delete m_recently;
}


/**
 * @fn favorites
 */
FavoritesCore *QuadroCore::favorites()
{
    return m_favorites;
}


/**
 * @fn filemanager
 */
FileManagerCore *QuadroCore::filemanager()
{
    return m_filemanager;
}


/**
 * @fn launcher
 */
LauncherCore *QuadroCore::launcher()
{
    return m_launcher;
}


/**
 * @fn plugin
 */
PluginCore *QuadroCore::plugin()
{
    return m_plugin;
}


/**
 * @fn recently
 */
RecentlyCore *QuadroCore::recently()
{
    return m_recently;
}


/**
 * @fn createDBusSession
 */
void QuadroCore::createDBusSession()
{
    QDBusConnection bus = QDBusConnection::sessionBus();
    if (!bus.registerService(DBUS_SERVICE)) {
        qCWarning(LOG_UI) << "Could not register service";
        qCWarning(LOG_UI) << bus.lastError().message();
    }
    if (!bus.registerObject(DBUS_OBJECT_PATH,
                            new QuadroAdaptor(this),
                            QDBusConnection::ExportAllContents)) {
        qCWarning(LOG_UI) << "Could not register library object";
        qCWarning(LOG_UI) << bus.lastError().message();
    }
}
