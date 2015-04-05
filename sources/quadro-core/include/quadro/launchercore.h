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
 * @file launchercore.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef LAUNCHERCORE_H
#define LAUNCHERCORE_H

#include <QObject>


/**
 * @brief The LauncherCore class provides launcher backend
 */
class LauncherCore : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief LauncherCore class constructor
     * @param debugCmd       show debug messages
     */
    explicit LauncherCore(const bool debugCmd = false);
    /**
     * @brief LauncherCore class destructor
     */
    ~LauncherCore();

public slots:
    /**
     * @brief init application using given paths
     * @param paths          shell $PATH variable
     */
    void initApplications(const QStringList paths = QStringList());

private:
    /**
     * @brief show debug messages. Default is false
     */
    bool debug = false;
}


#endif /* LAUNCHERCORE_H */
