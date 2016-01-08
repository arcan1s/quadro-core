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
 * @file configmanageradaptor.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadrocore/quadro.h"

#include <QMetaProperty>


/**
 * @class ConfigManagerAdaptor
 */
/**
 * @fn ConfigManagerAdaptor
 */
ConfigManagerAdaptor::ConfigManagerAdaptor(ConfigManager *manager)
    : QDBusAbstractAdaptor(manager),
      m_manager(manager)
{
    qCDebug(LOG_DBUS) << __PRETTY_FUNCTION__;
}


/**
 * @fn ~ConfigManagerAdaptor
 */
ConfigManagerAdaptor::~ConfigManagerAdaptor()
{
    qCDebug(LOG_DBUS) << __PRETTY_FUNCTION__;
}


/**
 * @fn Defaults
 */
void ConfigManagerAdaptor::Defaults()
{
    m_manager->readSettings(true);
}


/**
 * @fn Get
 */
QDBusVariant ConfigManagerAdaptor::Get(const QString key) const
{
    qCDebug(LOG_DBUS) << "Ask for value with key" << key;

    return QDBusVariant(m_manager->property(key.toStdString().c_str()));
}


/**
 * @fn KnownKeys
 */
QStringList ConfigManagerAdaptor::KnownKeys() const
{
    QStringList keys;
    for (int i=0; i<m_manager->metaObject()->propertyCount(); i++)
        keys.append(QString::fromUtf8(m_manager->metaObject()->property(i).name()));

    return keys;
}


/**
 * @fn Read
 */
void ConfigManagerAdaptor::Read()
{
    m_manager->readSettings(false);
}


/**
 * @fn Save
 */
bool ConfigManagerAdaptor::Save() const
{
    return m_manager->saveSettings();
}


/**
 * @fn Set
 */
bool ConfigManagerAdaptor::Set(const QString key, const QDBusVariant value)
{
    qCDebug(LOG_DBUS) << "Set value" << value.variant() << "for key" << key;

    QVariantHash dict;
    dict[key] = value.variant();

    return m_manager->setSettings(dict);
}


/**
 * @fn Update
 */
bool ConfigManagerAdaptor::Update(const QDBusVariant other)
{
    qCDebug(LOG_DBUS) << "Set values" << other.variant();

    QVariantHash dict = other.variant().toHash();

    return m_manager->setSettings(dict);
}


/*
 * @fn Verify
 */
bool ConfigManagerAdaptor::Verify(const QString key,
                                  const QDBusVariant value) const
{
    qCDebug(LOG_DBUS) << "Verify value" << value.variant() << "for key" << key;

    QVariantHash dict;
    dict[key] = value.variant();

    bool ok;
    m_manager->verifySettings(dict, &ok);

    return ok;
}
