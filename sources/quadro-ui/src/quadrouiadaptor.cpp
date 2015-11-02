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


#include "quadrouiadaptor.h"

#include "mainwindow.h"
#include "quadro/quadrodebug.h"


QuadroUiAdaptor::QuadroUiAdaptor(MainWindow *parent)
    : QDBusAbstractAdaptor(parent),
      mainWindow(parent)
{
    qCDebug(LOG_DBUS) << __PRETTY_FUNCTION__;
}


QuadroUiAdaptor::~QuadroUiAdaptor()
{
    qCDebug(LOG_DBUS) << __PRETTY_FUNCTION__;
}


void QuadroUiAdaptor::RunContainer(const QString exec)
{
    qCDebug(LOG_DBUS) << "Run container with" << exec;

    return mainWindow->createContainer(exec);
}
