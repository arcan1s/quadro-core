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
LauncherCore::LauncherCore(QObject *parent, const bool debugCmd)
    : AbstractAppAggregator(parent, debugCmd),
      debug(debugCmd)
{
}


/**
 * @fn ~LauncherCore
 */
LauncherCore::~LauncherCore()
{
    if (debug) qDebug() << PDEBUG;

    m_applicationsFromPaths.clear();
}


/**
 * @fn applicationsFromPaths
 */
QMap<QString, ApplicationItem *> LauncherCore::applicationsFromPaths() const
{
    if (debug) qDebug() << PDEBUG;

    return m_applicationsFromPaths;
}


/**
 * @fn applicationsBySubstr
 */
QMap<QString, ApplicationItem *> LauncherCore::applicationsBySubstr(const QString _substr) const
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Substring" << _substr;

    QMap<QString, ApplicationItem *> apps = AbstractAppAggregator::applicationsBySubstr(_substr);
    if (m_applicationsFromPaths.contains(_substr))
        apps[_substr] = m_applicationsFromPaths[_substr];

    return apps;
}


/**
 * @fn initApplications
 */
void LauncherCore::initApplications()
{
    if (debug) qDebug() << PDEBUG;

    // start cleanup
    dropApplications();
    m_applicationsFromPaths.clear();

    QMap<QString, ApplicationItem *> desktops = getApplicationsFromDesktops();
    for (int i=0; i<desktops.keys().count(); i++) {
        if (!desktops[desktops.keys()[i]]->shouldBeShown()) continue;
        addApplication(desktops[desktops.keys()[i]]);
    }
    m_applicationsFromPaths = getApplicationsFromPaths();

    // cleanup
    desktops.clear();
}


/**
 * @fn getApplicationsFromDesktops
 */
QMap<QString, ApplicationItem *> LauncherCore::getApplicationsFromDesktops()
{
    if (debug) qDebug() << PDEBUG;

    QStringList filter("*.desktop");
    QStringList desktopPaths = QStandardPaths::standardLocations(QStandardPaths::ApplicationsLocation);
    // append from subdirectories
    for (int i=desktopPaths.count()-1; i>=0; i--) {
        QStringList entries = QDir(desktopPaths[i]).entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        for (int j=0; j<entries.count(); j++)
            desktopPaths.append(QString("%1/%2").arg(desktopPaths[i]).arg(entries[j]));
    }
    // show
    if (debug) qDebug() << PDEBUG << ":" << "Paths" << desktopPaths;
    QMap<QString, ApplicationItem *> items;

    for (int i=desktopPaths.count()-1; i>=0; i--) {
        QStringList entries = QDir(desktopPaths[i]).entryList(filter, QDir::Files);
        for (int j=0; j<entries.count(); j++) {
            QString desktop = QFileInfo(QDir(desktopPaths[i]), entries[j]).filePath();
            if (debug) qDebug() << PDEBUG << ":" << "Desktop" << desktop;
            ApplicationItem *item = ApplicationItem::fromDesktop(desktop, this, debug);
            items[item->name()] = item;
        }
    }

    return items;
}


/**
 * @fn getApplicationsFromPaths
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
            if (!QFileInfo(executable).isExecutable()) continue;
            if (debug) qDebug() << PDEBUG << ":" << "Executable" << executable;
            ApplicationItem *item = new ApplicationItem(this, executable);
            items[item->name()] = item;
        }
    }

    return items;
}
