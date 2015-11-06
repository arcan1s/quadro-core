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
 * @file pluginadaptor.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadro/quadro.h"


/**
 * @class PluginAdaptor
 */
/**
 * @fn PluginAdaptor
 */
PluginAdaptor::PluginAdaptor(QObject *parent, PluginInterface *plugin)
    : QDBusAbstractAdaptor(parent),
      m_plugin(plugin)
{
    qCDebug(LOG_PL) << __PRETTY_FUNCTION__;
}


/**
 * @fn ~PluginAdaptor
 */
PluginAdaptor::~PluginAdaptor()
{
    qCDebug(LOG_PL) << __PRETTY_FUNCTION__;
}


/**
 * @fn Ping
 */
bool PluginAdaptor::Ping()
{
    return true;
}


/**
 * @fn Api
 */
int PluginAdaptor::Api()
{
    return m_plugin->api();
}


/**
 * @fn Background
 */
QString PluginAdaptor::Background()
{
    return m_plugin->background();
}


/**
 * @fn Data
 */
QString PluginAdaptor::Data()
{
    return m_plugin->data();
}


/**
 * @fn Name
 */
QString PluginAdaptor::Name()
{
    return m_plugin->name();
}


/**
 * @fn Action
 */
void PluginAdaptor::Action()
{
    return m_plugin->action();
}


/**
 * @fn Close
 */
void PluginAdaptor::Close()
{
    return m_plugin->quit();
}


/**
 * @fn ReadSettings
 */
void PluginAdaptor::ReadSettings(const QString desktopPath)
{
    return m_plugin->readSettings(desktopPath);
}


/**
 * @fn SaveSettings
 */
bool PluginAdaptor::SaveSettings(const QString desktopPath)
{
    return m_plugin->saveSettings(desktopPath);
}


/**
 * @fn Update
 */
void PluginAdaptor::Update()
{
    return m_plugin->update();
}
