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


#include "QuadroUiAdaptor.h"

#include <unistd.h>

#include <quadrocore/QuadroDebug.h>

#include "QuadroMainWindow.h"


QuadroUiAdaptor::QuadroUiAdaptor(QuadroMainWindow *_parent)
    : QDBusAbstractAdaptor(_parent)
    , m_mainWindow(_parent)
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


void QuadroUiAdaptor::RunContainer(const QStringList &_exec,
                                   const QString &_name) const
{
    qCDebug(LOG_DBUS) << "Run container with" << _exec << _name;

    return m_mainWindow->createContainer(_exec, _name);
}


void QuadroUiAdaptor::RunWebContainer(const QString &_url,
                                      const bool _showOpen) const
{
    qCDebug(LOG_DBUS) << "Run container with url" << _url
                      << "with show open button" << _showOpen;

    return m_mainWindow->createWebContainer(_url, _showOpen);
}


QStringList QuadroUiAdaptor::UIDs() const
{
    QStringList uids;
    uids.append(QString::number(getuid()));
    uids.append(QString::number(geteuid()));

    return uids;
}
