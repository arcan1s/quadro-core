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
#include <QDir>
#include <QProcessEnvironment>
#include <QStandardPaths>

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
 * @fn getApplicationsFromDesktops
 */
QMap<QString, ApplicationItem *> LauncherCore::getApplicationsFromDesktops()
{
    if (debug) qDebug() << PDEBUG;

    QStringList desktopPaths = QStandardPaths::standardLocations(QStandardPaths::ApplicationsLocation);
    if (debug) qDebug() << PDEBUG << ":" << "Paths" << desktopPaths;
    QMap<QString, ApplicationItem *> items;

    for (int i=desktopPaths.count()-1; i>=0; i--) {
        QStringList entries = QDir(desktopPaths[i]).entryList(QDir::Files);
        for (int j=0; j<entries.count(); j++) {
            QString desktop = QFileInfo(QDir(desktopPaths[i]), entries[j]).filePath();
            if (debug) qDebug() << PDEBUG << ":" << "Desktop" << desktop;
            ApplicationItem *item = ApplicationItem::fromDesktop(desktop);
            items[item->name()] = item;
        }
    }

    return items;
}


/**
 * @fn getApplicationsFromDesktops
 */
QMap<QString, ApplicationItem *> LauncherCore::getApplicationsFromPaths()
{
    if (debug) qDebug() << PDEBUG;

    QProcessEnvironment environment = QProcessEnvironment::systemEnvironment();
    QString pathVariable = environment.value(QString("PATH"));
    QStringList paths = pathVariable.split(QChar(':'));
    if (debug) qDebug() << PDEBUG << ":" << "Paths" << paths;
    QMap<QString, ApplicationItem *> items;

    for (int i=0; i<paths.count(); i++) {
        QStringList entries = QDir(paths[i]).entryList(QDir::Files);
        for (int j=0; j<entries.count(); j++) {
            QString executable = QFileInfo(QDir(paths[i]), entries[j]).filePath();
            if (debug) qDebug() << PDEBUG << ":" << "Executable" << executable;
            ApplicationItem *item = new ApplicationItem(executable);
            items[item->name()] = item;
        }
    }

    return items;
}


/**
 * @fn initApplications
 */
void LauncherCore::initApplications(const QStringList paths)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Paths" << paths;
}
