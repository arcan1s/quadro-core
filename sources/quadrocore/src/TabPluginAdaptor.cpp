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
 * @file TabPluginAdaptor.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadrocore/Quadro.h"

using namespace Quadro;


/**
 * @class TabPluginAdaptor
 */
/**
 * @fn TabPluginAdaptor
 */
TabPluginAdaptor::TabPluginAdaptor(QObject *_parent,
                                   TabPluginInterface *_plugin)
    : QuadroPluginAdaptor(_parent, _plugin)
    , m_plugin(_plugin)
{
    qCDebug(LOG_DBUS) << __PRETTY_FUNCTION__;
}


/**
 * @fn ~TabPluginAdaptor
 */
TabPluginAdaptor::~TabPluginAdaptor()
{
    qCDebug(LOG_DBUS) << __PRETTY_FUNCTION__;
}


/**
 * @fn Update
 */
void TabPluginAdaptor::Update()
{
    return m_plugin->init();
}
