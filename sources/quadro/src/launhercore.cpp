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
    : QObject(parent),
      debug(debugCmd)
{
}


/**
 * @fn ~LauncherCore
 */
LauncherCore::~LauncherCore()
{
    if (debug) qDebug() << PDEBUG;

    m_applications.clear();
}


/**
 * @fn applications
 */
QMap<QString, ApplicationItem *> LauncherCore::applications()
{
    if (debug) qDebug() << PDEBUG;

    return m_applications;
}


/**
 * @fn applicationsFromPaths
 */
QMap<QString, ApplicationItem *> LauncherCore::applicationsFromPaths()
{
    if (debug) qDebug() << PDEBUG;

    return m_applicationsFromPaths;
}


/**
 * @fn applicationsByCategory
 */
QMap<QString, ApplicationItem *> LauncherCore::applicationsByCategory(const QString _category)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Category" << _category;

    QMap<QString, ApplicationItem *> apps;
    if (!availableCategories().contains(_category)) {
        if (debug) qDebug() << PDEBUG << ":" << "Incorrect category" << _category;
        return apps;
    }

    for (int i=0; i<m_applications.keys().count(); i++) {
        QString key = m_applications.keys()[i];
        QStringList categories = m_applications[key]->categories();
        if (!categories.contains(_category)) continue;
        apps[key] = m_applications[key];
    }

    return apps;
}


/**
 * @fn applicationsBySubstr
 */
QMap<QString, ApplicationItem *> LauncherCore::applicationsBySubstr(const QString _substr)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Substring" << _substr;

    QMap<QString, ApplicationItem *> apps;
    // from desktops
    QStringList keys = static_cast<QStringList>(m_applications.keys()).filter(_substr, Qt::CaseInsensitive);
    for (int i=0; i<keys.count(); i++)
        apps[keys[i]] = m_applications[keys[i]];
    // from path
    if (m_applicationsFromPaths.contains(_substr))
        apps[_substr] = m_applicationsFromPaths[_substr];

    return apps;
}


/**
 * @fn availableCategories
 */
QStringList LauncherCore::availableCategories()
{
    if (debug) qDebug() << PDEBUG;
    // refer to http://standards.freedesktop.org/menu-spec/latest/apa.html

    QStringList categories;
    categories.append(QString("AudioVideo"));       // usually named as Multimedia
    categories.append(QString("Audio"));
    categories.append(QString("Video"));
    categories.append(QString("Development"));
    categories.append(QString("Education"));
    categories.append(QString("Game"));
    categories.append(QString("Graphics"));
    categories.append(QString("Network"));
    categories.append(QString("Office"));
    categories.append(QString("Science"));
    categories.append(QString("Settings"));
    categories.append(QString("System"));
    categories.append(QString("Utility"));

    if (debug) qDebug() << PDEBUG << ":" << "Found categories" << categories;
    return categories;
}


/**
 * @fn hasApplication
 */
bool LauncherCore::hasApplication(const QString _name)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Application name" << _name;

    return m_applications.contains(_name);
}


/**
 * @fn initApplications
 */
void LauncherCore::initApplications()
{
    if (debug) qDebug() << PDEBUG;

    // start cleanup
    m_applications.clear();
    m_applicationsFromPaths.clear();

    QMap<QString, ApplicationItem *> desktops = getApplicationsFromDesktops();
    for (int i=0; i<desktops.keys().count(); i++) {
        if (!desktops[desktops.keys()[i]]->shouldBeShown()) continue;
        m_applications[desktops.keys()[i]] = desktops[desktops.keys()[i]];
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
