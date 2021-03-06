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
 * @file PluginContainer.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadroui/QuadroUi.h"

#include <QLayout>

#include <quadrocore/Quadro.h>

using namespace Quadro;


/**
 * @class PluginContainer
 */
/**
 * @fn PluginContainer
 */
PluginContainer::PluginContainer(QWidget *_parent, const int _grid,
                                 const QString _widgetTitle,
                                 const Qt::ScrollBarPolicy _hPolicy,
                                 const Qt::ScrollBarPolicy _vPolicy)
    : QuadroWidget(_parent, _grid, _widgetTitle, _hPolicy, _vPolicy)
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
    qCDebug(LOG_UILIB) << "Add plugin" << _interface->name() << "to position"
                       << widget()->layout()->count();

    QSize widgetSize = QSize(_interface->widgetSize().width() * grid(),
                             _interface->widgetSize().height() * grid());
    widget()->layout()->addWidget(
        new PluginWidget(_interface, widgetSize, this));
}
