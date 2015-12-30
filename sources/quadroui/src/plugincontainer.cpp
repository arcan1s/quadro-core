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
 * @file plugincontainer.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadroui/quadroui.h"

#include <QLayout>

#include <quadrocore/quadro.h>


/**
 * @class PluginContainer
 */
/**
 * @fn PluginContainer
 */
PluginContainer::PluginContainer(QWidget *parent, const float grid,
                                 const QString widgetTitle,
                                 const Qt::ScrollBarPolicy hPolicy,
                                 const Qt::ScrollBarPolicy vPolicy)
    : QuadroWidget(parent, grid, widgetTitle, hPolicy, vPolicy)
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;
}


/**
 * @fn ~PluginContainer
 */
PluginContainer::~PluginContainer()
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;

    clearLayout();
}


/**
 * @fn addPlugin
 */
void PluginContainer::addPlugin(PluginInterface *_interface)
{
    qCDebug(LOG_UILIB) << "Add plugin" << _interface->name() << "to position" << widget()->layout()->count();

    QSize widgetSize = QSize(_interface->widgetSize().width() * grid(),
                             _interface->widgetSize().height() * grid());
    widget()->layout()->addWidget(new PluginWidget(_interface, widgetSize, this));
}
