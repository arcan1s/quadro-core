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

#include <unistd.h>

#include <quadrocore/quadrodebug.h>

#include "mainwindow.h"


QuadroUiAdaptor::QuadroUiAdaptor(MainWindow *parent)
    : QDBusAbstractAdaptor(parent),
      m_mainWindow(parent)
{
    qCDebug(LOG_DBUS) << __PRETTY_FUNCTION__;
}


QuadroUiAdaptor::~QuadroUiAdaptor()
{
    qCDebug(LOG_DBUS) << __PRETTY_FUNCTION__;
}


bool QuadroUiAdaptor::Active() const
{
    return true;
}


void QuadroUiAdaptor::ChangeState() const
{
    if (m_mainWindow->isHidden())
        return Restore();
    else
        return Hide();
}


void QuadroUiAdaptor::Close() const
{
    return m_mainWindow->closeMainWindow();
}


void QuadroUiAdaptor::Hide() const
{
    return m_mainWindow->hide();
}


void QuadroUiAdaptor::Restore() const
{
    return m_mainWindow->show();
}


void QuadroUiAdaptor::RunContainer(const QString exec, const QString name) const
{
    qCDebug(LOG_DBUS) << "Run container with" << exec << name;

    return m_mainWindow->createContainer(exec, name);
}


QStringList QuadroUiAdaptor::UIDs() const
{
    QStringList uids;
    uids.append(QString::number(getuid()));
    uids.append(QString::number(geteuid()));

    return uids;
}
