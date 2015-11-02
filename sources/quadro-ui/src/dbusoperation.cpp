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


#include "dbusoperation.h"

#include <QDBusConnection>
#include <QDBusMessage>

#include "quadro/config.h"
#include "quadro/quadrodebug.h"


QVariantList sendRequest(const QString service, const QString path, const QString interface,
                         const QString cmd, const QVariantList args)
{
    qCDebug(LOG_DBUS) << "Service" << service << "with interface" << interface;
    qCDebug(LOG_DBUS) << "Path" << path << "with command" << cmd;
    qCDebug(LOG_DBUS) << "Arguments" << args;

    QDBusConnection bus = QDBusConnection::sessionBus();
    QDBusMessage request = QDBusMessage::createMethodCall(service, path, interface, cmd);
    if (!args.isEmpty())
        request.setArguments(args);

    QDBusMessage response = bus.call(request, QDBus::BlockWithGui);
    QVariantList arguments = response.arguments();
    qCInfo(LOG_DBUS) << "Error message" << response.errorMessage();

    return arguments;
}


QVariantList sendRequestToLibrary(const QString cmd, const QVariantList args)
{
    qCDebug(LOG_DBUS) << "Command" << cmd << "with args" << args;

    return sendRequest(QString(DBUS_SERVICE), QString(DBUS_OBJECT_PATH),
                       QString(DBUS_INTERFACE), cmd, args);
}


QVariantList sendRequestToPlugin(const QString plugin, const QString cmd,
                                 const QVariantList args)
{
    qCDebug(LOG_DBUS) << "Plugin name" << plugin;
    qCDebug(LOG_DBUS) << "Command" << cmd << "with args" << args;

    return sendRequest(QString(DBUS_PLUGIN_SERVICE), QString("/%1").arg(plugin),
                       QString(DBUS_PLUGIN_INTERFACE), cmd, args);
}


QVariantList sendRequestToUi(const QString cmd, const QVariantList args)
{
    qCDebug(LOG_DBUS) << "Command" << cmd << "with args" << args;

    return sendRequest(QString(DBUS_SERVICE), QString(DBUS_UI_OBJECT_PATH),
                       QString(DBUS_INTERFACE), cmd, args);
}
