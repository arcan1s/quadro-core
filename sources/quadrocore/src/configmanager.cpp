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
 * @file configmanager.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadrocore/quadro.h"

#include <QSettings>
#include <QStandardPaths>


/**
 * @class ConfigManager
 */
/**
 * @fn ConfigManager
 */
ConfigManager::ConfigManager(QObject *parent)
    : QObject(parent)
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;

    m_path = QStandardPaths::locate(QStandardPaths::ConfigLocation,
                                    QString("quadro.conf"));
    qCInfo(LOG_LIB) << "Use file path" << m_path;

    readSettings();
}


/**
 * @fn ~ConfigManager
 */
ConfigManager::~ConfigManager()
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;
}


/**
 * @fn setSettings
 */
bool ConfigManager::setSettings(const QVariantHash &_other)
{
    qCDebug(LOG_LIB) << "Set settings from" << _other;

    bool ok;
    QStringList error = verifySettings(_other, &ok);
    if (!ok) {
        qCCritical(LOG_LIB) << "Invalid keys found" << error;
        return false;
    }

    for (auto key : _other.keys())
        m_configuration[key] = _other[key];

    return true;
}


/**
 * @fn verifySettings
 */
QStringList ConfigManager::verifySettings(const QVariantHash &_other, bool *_ok)
{
    qCDebug(LOG_LIB) << "Verify settings" << _other;

    QStringList error;

    if ((_other.contains(QString("GridSize")))
        && _other[QString("GridSize")].toInt() <= 0) {
        error.append(QString("GridSize"));
    }
    if ((_other.contains(QString("RecentItemCount")))
        && _other[QString("RecentItemCount")].toInt() < 0) {
        error.append(QString("RecentItemCount"));
    }
    if ((_other.contains(QString("ShowHidden")))
        && _other[QString("ShowHidden")].type() != QVariant::Bool) {
        error.append(QString("ShowHidden"));
    }

    if (_ok != nullptr)
        *_ok = error.isEmpty();
    return error;
}


/**
 * @fn path
 */
QString ConfigManager::path() const
{
    return m_path;
}


/**
 * @fn gridSize
 */
int ConfigManager::gridSize() const
{
    return m_configuration[QString("GridSize")].toInt();
}


/**
 * @fn recentItemCount
 */
int ConfigManager::recentItemCount() const
{
    return m_configuration[QString("RecentItemCount")].toInt();
}


/**
 * @fn showHidden
 */
bool ConfigManager::showHidden() const
{
    return m_configuration[QString("ShowHidden")].toBool();
}


/**
 * @fn readSettings
 */
void ConfigManager::readSettings(const bool _defaults)
{
    qCDebug(LOG_LIB) << "Read default settings" << _defaults;

    QSettings settings(_defaults ? QString("/dev/null") : m_path, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");

    settings.beginGroup(QString("Global"));
    m_configuration[QString("GridSize")] = settings.value(QString("GridSize"), 150);
    m_configuration[QString("RecentItemsCount")] = settings.value(QString("RecentItemsCount"), 20);
    m_configuration[QString("ShowHidden")] = settings.value(QString("ShowHidden"), false);
    settings.endGroup();

    for (auto key : m_configuration.keys())
        qCInfo(LOG_PL) << key << "=" << m_configuration[key];
}


/**
 * @fn saveSettings
 */
bool ConfigManager::saveSettings() const
{
    QSettings settings(m_path, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");

    settings.beginGroup(QString("Global"));
    settings.setValue(QString("GridSize"), m_configuration[QString("GridSize")]);
    settings.setValue(QString("RecentItemsCount"), m_configuration[QString("RecentItemsCount")]);
    settings.setValue(QString("ShowHidden"), m_configuration[QString("ShowHidden")]);
    settings.endGroup();

    settings.sync();

    return settings.status() == QSettings::NoError;
}
