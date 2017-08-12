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
 * @file DesktopInterface.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef DESKTOPINTERFACE_H
#define DESKTOPINTERFACE_H

#include <QHash>
#include <QtPlugin>

#include "Config.h"


/**
 * @namespace Quadro
 */
namespace Quadro
{
/**
 * @brief The DesktopInterface class provides adaptor to WM
 */
class DesktopInterface
{
public:
    /**
     * @brief DesktopInterface class destructor
     */
    virtual ~DesktopInterface(){};
    /**
     * @brief get WIds by given PID
     * @param _pid PID
     * @return list of WIds
     */
    virtual QList<unsigned long long> getWindowByPid(const long long _pid) = 0;
    /**
     * @brief get active windows
     * @return map of windows keys of which are Q_PIDs
     */
    virtual QHash<long long, unsigned long long> getWindowsList() = 0;
};
};

Q_DECLARE_INTERFACE(Quadro::DesktopInterface, DESKTOP_INTERFACE)


#endif /* DESKTOPINTERFACE_H */
