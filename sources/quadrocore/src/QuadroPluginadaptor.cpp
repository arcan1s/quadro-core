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
 * @file QuadroPluginadaptor.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadrocore/Quadro.h"

using namespace Quadro;


/**
 * @class QuadroPluginAdaptor
 */
/**
 * @fn QuadroPluginAdaptor
 */
QuadroPluginAdaptor::QuadroPluginAdaptor(QObject *_parent,
                                         QuadroPluginInterface *_plugin)
    : QDBusAbstractAdaptor(_parent)
    , m_plugin(_plugin)
{
    qCDebug(LOG_DBUS) << __PRETTY_FUNCTION__;
}


/**
 * @fn ~QuadroPluginAdaptor
 */
QuadroPluginAdaptor::~QuadroPluginAdaptor()
{
    qCDebug(LOG_DBUS) << __PRETTY_FUNCTION__;
}


/**
 * @fn Ping
 */
bool QuadroPluginAdaptor::Ping() const
{
    return true;
}


/**
 * @fn Name
 */
QString QuadroPluginAdaptor::Name() const
{
    return m_plugin->name();
}


/**
 * @fn Init
 */
void QuadroPluginAdaptor::Init()
{
    return m_plugin->init();
}


/**
 * @fn Quit
 */
void QuadroPluginAdaptor::Quit(const QString &configPath)
{
    qCDebug(LOG_DBUS) << "Configuration file" << configPath;

    return m_plugin->quit(configPath);
}


/**
 * @fn ReadSettings
 */
void QuadroPluginAdaptor::ReadSettings(const QString &configPath)
{
    qCDebug(LOG_DBUS) << "Configuration file" << configPath;

    return m_plugin->readSettings(configPath);
}


/**
 * @fn SaveSettings
 */
void QuadroPluginAdaptor::SaveSettings()
{
    return m_plugin->saveSettings();
}


/**
 * @fn WriteSettings
 */
bool QuadroPluginAdaptor::WriteSettings(const QString &configPath) const
{
    qCDebug(LOG_DBUS) << "Configuration file" << configPath;

    return m_plugin->writeSettings(configPath);
}
