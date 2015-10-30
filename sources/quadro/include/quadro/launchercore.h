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

#include <QMap>
#include <QStringList>

#include "abstractappaggregator.h"


/**
 * @brief The LauncherCore class provides launcher backend
 */
class LauncherCore : public AbstractAppAggregator
{
    Q_OBJECT

public:
    /**
     * @brief LauncherCore class constructor
     * @param parent         pointer to parent item
     */
    explicit LauncherCore(QObject *parent);
    /**
     * @brief LauncherCore class destructor
     */
    virtual ~LauncherCore();
    /**
     * @brief find applications from path variables
     * @return map of applications
     */
    QMap<QString, ApplicationItem *> applicationsFromPaths() const;
    /**
     * @brief find applications by substring in name
     * @param _substr        substring to which application need to be found
     * @return map of applications by substring
     */
    QMap<QString, ApplicationItem *> applicationsBySubstr(const QString _substr) const;


public slots:
    /**
     * @brief init application using given paths
     */
    void initApplications();

private:
    /**
     * @brief list of applications defined by PATH variable
     */
    QMap<QString, ApplicationItem *> m_applicationsFromPaths;
    /**
     * @brief return applications which has desktop files
     * @return map of generated ApplicationItem
     */
    QMap<QString, ApplicationItem *> getApplicationsFromDesktops();
    /**
     * @brief return applications which is placed to $PATH
     * @return map of generated ApplicationItem
     */
    QMap<QString, ApplicationItem *> getApplicationsFromPaths();
};


#endif /* LAUNCHERCORE_H */
