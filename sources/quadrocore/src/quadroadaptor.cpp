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
 * @file quadroadaptor.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadrocore/quadro.h"

#include <QMimeType>


/**
 * @class QuadroAdaptor
 */
/**
 * @fn QuadroAdaptor
 */
QuadroAdaptor::QuadroAdaptor(QuadroCore *core)
    : QDBusAbstractAdaptor(core),
      m_core(core)
{
    qCDebug(LOG_DBUS) << __PRETTY_FUNCTION__;
}


/**
 * @fn ~QuadroAdaptor
 */
QuadroAdaptor::~QuadroAdaptor()
{
    qCDebug(LOG_DBUS) << __PRETTY_FUNCTION__;
}


/**
 * @fn Favorites
 */
QStringList QuadroAdaptor::Favorites() const
{
    return m_core->favorites()->order();
}


/**
 * @fn Icon
 */
QString QuadroAdaptor::Icon(const QString _file) const
{
    qCDebug(LOG_DBUS) << "File name" << _file;

    return m_core->filemanager()->iconNameByFileName(_file);
}


/**
 * @fn IsKnownPlatform
 */
bool QuadroAdaptor::IsKnownPlatform() const
{
    return m_core->platformPlugin() != nullptr;
}


/**
 * @fn MIME
 */
QString QuadroAdaptor::MIME(const QString _file) const
{
    qCDebug(LOG_DBUS) << "File name" << _file;

    return m_core->filemanager()->mimeByFileName(_file).name();
}


/**
 * @fn Recent
 */
QStringList QuadroAdaptor::Recent() const
{
    return m_core->recently()->recent();
}


/**
 * @fn UpdateApplications
 */
void QuadroAdaptor::UpdateApplications() const
{
    m_core->launcher()->initApplications();
}


/**
 * @fn UpdateFavorites
 */
void QuadroAdaptor::UpdateFavorites() const
{
    m_core->favorites()->initApplications();
}


/**
 * @fn UpdateRecent
 */
void QuadroAdaptor::UpdateRecent() const
{
    m_core->recently()->initApplications();
}


/**
 * @fn WIdForPID
 */
QStringList QuadroAdaptor::WIdForPID(const long long _pid)
{
    qCDebug(LOG_DBUS) << "Search for PID" << _pid;

    if (!IsKnownPlatform())
        return QStringList();

    QList<unsigned long long> wIds = m_core->platformPlugin()->getWindowByPid(_pid);
    QStringList output;
    for (auto id : wIds)
        output.append(QString::number(id));

    return output;
}
