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


#include "quadrocore/quadro.h"

#include <QDBusConnection>
#include <QDBusMessage>


/**
 * @fn sendRequest
 */
QVariantList DBusOperations::sendRequest(const QString _service, const QString _path,
                                         const QString _interface,
                                         const QString _cmd,
                                         const QVariantList _args)
{
    qCDebug(LOG_DBUS) << "Service" << _service << "with interface" << _interface;
    qCDebug(LOG_DBUS) << "Path" << _path << "with command" << _cmd;
    qCDebug(LOG_DBUS) << "Arguments" << _args;

    QDBusConnection bus = QDBusConnection::sessionBus();
    QDBusMessage request = QDBusMessage::createMethodCall(_service, _path, _interface, _cmd);
    if (!_args.isEmpty())
        request.setArguments(_args);

    QDBusMessage response = bus.call(request, QDBus::BlockWithGui);
    QVariantList arguments = response.arguments();
    qCInfo(LOG_DBUS) << "Error message" << response.errorMessage();

    return arguments;
}


/**
 * @fn sendRequestToLibrary
 */
QVariantList DBusOperations::sendRequestToLibrary(const QString _cmd, const QVariantList _args)
{
    qCDebug(LOG_DBUS) << "Command" << _cmd << "with args" << _args;

    return sendRequest(QString(DBUS_SERVICE), QString(DBUS_OBJECT_PATH),
                       QString(DBUS_INTERFACE), _cmd, _args);
}


/**
 * @fn sendRequestToPlugin
 */
QVariantList DBusOperations::sendRequestToPlugin(const QString _plugin,
                                                 const QString _cmd,
                                                 const QVariantList _args)
{
    qCDebug(LOG_DBUS) << "Plugin name" << _plugin;
    qCDebug(LOG_DBUS) << "Command" << _cmd << "with args" << _args;

    return sendRequest(QString(DBUS_PLUGIN_SERVICE), QString("/%1").arg(_plugin),
                       QString(DBUS_PLUGIN_INTERFACE), _cmd, _args);
}


/**
 * @fn sendRequestToUi
 */
QVariantList DBusOperations::sendRequestToUi(const QString _cmd, const QVariantList _args)
{
    qCDebug(LOG_DBUS) << "Command" << _cmd << "with args" << _args;

    return sendRequest(QString(DBUS_SERVICE), QString(DBUS_UI_OBJECT_PATH),
                       QString(DBUS_INTERFACE), _cmd, _args);
}