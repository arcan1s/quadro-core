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
 * @file DBusOperations.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef DBUSOPERATIONS_H
#define DBUSOPERATIONS_H

#include <QDBusArgument>
#include <QVariant>


/**
 * @namespace Quadro
 */
namespace Quadro
{
/**
 * @namespace DBusOperations
 * @brief methods provide common operations with DBus
 */
namespace DBusOperations
{
/**
 * @brief additional method to avoid conversion from DBus type to native ones
 * @tparam T type to which DBus data should be converted
 * @param _data source data
 * @return converted value
 */
template <class T> T toNativeType(const QVariant _data)
{
    return qdbus_cast<T>(
        _data.value<QDBusVariant>().variant().value<QDBusArgument>());
};

/**
 * @brief common DBus request
 * @param _service DBus service name
 * @param _path DBus object path
 * @param _interface DBus interface name
 * @param _cmd command which will be sent to DBus
 * @param _args command arguments
 * @return reply object from DBus request
 */
QVariantList sendRequest(const QString &_service, const QString &_path,
                         const QString &_interface, const QString &_cmd,
                         const QVariantList &_args);

/**
 * @brief DBus request to configuration manager
 * @param _cmd command which will be sent to DBus
 * @param _args command arguments if any
 * @return DBusOperations::sendRequest()
 */
QVariantList sendRequestToConfig(const QString &_cmd,
                                 const QVariantList &_args = QVariantList());

/**
 * @brief DBus request to library
 * @param _cmd command which will be sent to DBus
 * @param _args command arguments if any
 * @return DBusOperations::sendRequest()
 */
QVariantList sendRequestToLibrary(const QString &_cmd,
                                  const QVariantList &_args = QVariantList());

/**
 * @brief DBus request to plugin
 * @param _index plugin index
 * @param _cmd command which will be sent to DBus
 * @param _args command arguments if any
 * @return DBusOperations::sendRequest()
 */
QVariantList sendRequestToPlugin(const int _index, const QString &_cmd,
                                 const QVariantList &_args = QVariantList());

/**
 * @brief DBus request to ui
 * @param _cmd command which will be sent to DBus
 * @param _args command arguments if any
 * @return DBusOperations::sendRequest()
 */
QVariantList sendRequestToUi(const QString &_cmd,
                             const QVariantList &_args = QVariantList());
};
};


#endif /* DBUSOPERATIONS_H */
