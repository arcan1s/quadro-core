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
 * @file ConfigManagerAdaptor.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef CONFIGMANAGERADAPTOR_H
#define CONFIGMANAGERADAPTOR_H

#include <QDBusAbstractAdaptor>
#include <QDBusVariant>
#include <QObject>

#include "Config.h"


/**
 * @namespace Quadro
 */
namespace Quadro
{
class ConfigManager;

/**
 * @brief The ConfigManagerAdaptor class provides configuration manager DBus
 * adaptor
 */
class ConfigManagerAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", DBUS_INTERFACE_NAME)

public:
    /**
     * @brief ConfigManagerAdaptor class constructor
     * @param _manager pointer to configuration manager
     */
    explicit ConfigManagerAdaptor(ConfigManager *_manager);

    /**
     * @brief ConfigManagerAdaptor class destructor
     */
    virtual ~ConfigManagerAdaptor();

public slots:
    // public method interface
    /**
     * @brief read default settings
     */
    Q_NOREPLY void Defaults();

    /**
     * @brief configuration value by key
     * @param key key to search
     * @return value by specified key
     */
    QDBusVariant Get(const QString &key) const;

    /**
     * @brief known keys
     * @return list of known keys
     */
    QStringList KnownKeys() const;
    /**
     * @brief read settings
     */
    Q_NOREPLY void Read();

    /**
     * @brief save settings
     */
    bool Save() const;

    /**
     * @brief set value
     * @param key key to set
     * @param value value to set
     * @return true if value has been set successfully
     */
    bool Set(const QString &key, const QDBusVariant &value);

    /**
     * @brief update all values
     * @param other other settings dictionary
     * @return true if values were updated
     */
    bool Update(const QDBusVariant &other);

    /**
     * @brief verify value by key
     * @param key configuration key
     * @param value value associated with the key
     * @return true if no errors were found
     */
    bool Verify(const QString &key, const QDBusVariant &value) const;

private:
    // properties
    /**
     * @brief pointer to the configuration manager
     */
    ConfigManager *m_manager = nullptr;
};
};


#endif /* CONFIGMANAGERADAPTOR_H */
