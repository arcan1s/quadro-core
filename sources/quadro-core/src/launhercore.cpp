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
 * @file launchercore.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include <QDebug>

#include <quadro/quadro.h>
#include <pdebug/pdebug.h>


/**
 * @class LauncherCore
 */
/**
 * @fn LauncherCore
 */
LauncherCore::LauncherCore(const bool debugCmd)
    : debug(debugCmd)
{

}


/**
 * @fn ~LauncherCore
 */
LauncherCore::~LauncherCore()
{
    if (debug) qDebug() << PDEBUG;
}


/**
 * @fn initApplications
 */
void LauncherCore::initApplications(const QStringList paths)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Paths" << paths;
}
