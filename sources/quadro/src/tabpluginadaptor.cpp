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
 * @file tabpluginadaptor.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadro/quadro.h"


/**
 * @class TabPluginAdaptor
 */
/**
 * @fn TabPluginAdaptor
 */
TabPluginAdaptor::TabPluginAdaptor(QObject *parent, TabPluginItem *plugin)
    : QDBusAbstractAdaptor(parent),
      m_plugin(plugin)
{
    qCDebug(LOG_PL) << __PRETTY_FUNCTION__;
}


/**
 * @fn ~TabPluginAdaptor
 */
TabPluginAdaptor::~TabPluginAdaptor()
{
    qCDebug(LOG_PL) << __PRETTY_FUNCTION__;
}


/**
 * @fn Ping
 */
bool TabPluginAdaptor::Ping()
{
    return true;
}


/**
 * @fn Api
 */
int TabPluginAdaptor::Api()
{
    return m_plugin->api();
}


/**
 * @fn Name
 */
QString TabPluginAdaptor::Name()
{
    return m_plugin->name();
}


/**
 * @fn ReadSettings
 */
void TabPluginAdaptor::ReadSettings(const QString desktopPath)
{
    return m_plugin->readSettings(desktopPath);
}


/**
 * @fn SaveSettings
 */
bool TabPluginAdaptor::SaveSettings(const QString desktopPath)
{
    return m_plugin->saveSettings(desktopPath);
}


/**
 * @fn Update
 */
void TabPluginAdaptor::Update()
{
    return m_plugin->init();
}
