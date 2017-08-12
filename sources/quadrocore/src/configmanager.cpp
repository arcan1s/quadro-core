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
ConfigManager::ConfigManager(QObject *_parent)
    : QObject(_parent)
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;

    m_path
        = QStandardPaths::locate(QStandardPaths::ConfigLocation, "quadro.conf");
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

    for (auto &key : _other.keys())
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

    if ((_other.contains("GridSize")) && _other["GridSize"].toInt() <= 0) {
        error.append("GridSize");
    }
    if ((_other.contains("RecentItemCount"))
        && _other["RecentItemCount"].toInt() < 0) {
        error.append("RecentItemCount");
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
    return m_configuration["GridSize"].toInt();
}


/**
 * @fn recentItemCount
 */
int ConfigManager::recentItemCount() const
{
    return m_configuration["RecentItemCount"].toInt();
}


/**
 * @fn readSettings
 */
void ConfigManager::readSettings(const bool _defaults)
{
    qCDebug(LOG_LIB) << "Read default settings" << _defaults;

    QSettings settings(_defaults ? "/dev/null" : m_path, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");

    settings.beginGroup("Global");
    m_configuration["GridSize"] = settings.value("GridSize", 150);
    m_configuration["RecentItemsCount"]
        = settings.value("RecentItemsCount", 20);
    settings.endGroup();

    for (auto &key : m_configuration.keys())
        qCInfo(LOG_PL) << key << "=" << m_configuration[key];
}


/**
 * @fn saveSettings
 */
bool ConfigManager::saveSettings() const
{
    QSettings settings(m_path, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");

    settings.beginGroup("Global");
    for (auto &key : m_configuration.keys())
        settings.setValue(key, m_configuration[key]);
    settings.endGroup();

    settings.sync();

    return settings.status() == QSettings::NoError;
}
