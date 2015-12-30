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


#include "quadrocore/quadro.h"


/**
 * @class PluginAdaptor
 */
/**
 * @fn PluginAdaptor
 */
PluginAdaptor::PluginAdaptor(QObject *parent, PluginInterface *plugin)
    : QuadroPluginAdaptor(parent, plugin),
      m_plugin(plugin)
{
    qCDebug(LOG_DBUS) << __PRETTY_FUNCTION__;
}


/**
 * @fn ~PluginAdaptor
 */
PluginAdaptor::~PluginAdaptor()
{
    qCDebug(LOG_DBUS) << __PRETTY_FUNCTION__;
}


/**
 * @fn Background
 */
QString PluginAdaptor::Background() const
{
    return m_plugin->background();
}


/**
 * @fn Data
 */
QString PluginAdaptor::Data() const
{
    return m_plugin->data();
}


/**
 * @fn Action
 */
void PluginAdaptor::Action()
{
    return m_plugin->action();
}


/**
 * @fn MinimalSize
 */
QDBusVariant PluginAdaptor::Size() const
{
    return QDBusVariant(QVariant(m_plugin->widgetSize()));
}


/**
 * @fn Update
 */
void PluginAdaptor::Update()
{
    return m_plugin->update();
}


/**
 * @fn UpdateInterval
 */
int PluginAdaptor::UpdateInterval() const
{
    return m_plugin->updateInterval();
}
