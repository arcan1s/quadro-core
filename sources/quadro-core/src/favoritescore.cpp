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
 * @file favoritescore.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include <QDebug>
#include <QDir>

#include <quadro/quadro.h>
#include <pdebug/pdebug.h>

#include "version.h"


/**
 * @class FavoritesCore
 */
/**
 * @fn FavoritesCore
 */
FavoritesCore::FavoritesCore(const bool debugCmd)
    : debug(debugCmd)
{
}


/**
 * @fn ~FavoritesCore
 */
FavoritesCore::~FavoritesCore()
{
    if (debug) qDebug() << PDEBUG;

    m_applications.clear();
}


/**
 * @fn applications
 */
QMap<QString, ApplicationItem *> FavoritesCore::applications()
{
    if (debug) qDebug() << PDEBUG;

    return m_applications;
}


/**
 * @fn addToFavorites
 */
ApplicationItem *FavoritesCore::addToFavorites(const QString _executable,
                                               const QString _name,
                                               const QString _iconName)
{
    ApplicationItem *item = new ApplicationItem(_executable, _name);
    item->setIconByName(_iconName);

    if (!item->saveDesktop(desktopPath()).isEmpty()) {
        delete item;
        item = nullptr;
    }

    return item;
}


/**
 * @fn desktopPath
 */
QString FavoritesCore::desktopPath()
{
    return QString("%1/%2/%3").arg(QDir::homePath()).arg(HOME_PATH).arg(FAVORITES_PATH);
}


/**
 * @fn initApplications
 */
void FavoritesCore::initApplications()
{
    if (debug) qDebug() << PDEBUG;

    // start cleanup
    m_applications.clear();
    m_order.clear();

    m_applications = getApplicationsFromDesktops();
    m_order = getApplicationsOrder();
    sortApplications();
}


/**
 * @fn sortApplications
 */
void FavoritesCore::sortApplications()
{
    if (debug) qDebug() << PDEBUG;

    QMap<QString, ApplicationItem *> items;
    items.swap(m_applications);

    for (int i=0; i<m_order.count(); i++)
        m_applications[m_order[i]] = items.take(m_order[i]);
    items.clear();
}


/**
 * @fn getApplicationsFromDesktops
 */
QMap<QString, ApplicationItem *> FavoritesCore::getApplicationsFromDesktops()
{
    if (debug) qDebug() << PDEBUG;

    QMap<QString, ApplicationItem *> items;

    QStringList entries = QDir(desktopPath()).entryList(QDir::Files);
    for (int i=0; i<entries.count(); i++) {
        if (!entries.endsWith(QString(".desktop"))) continue;
        QString desktop = QFileInfo(QDir(desktopPath()), entries[i]).filePath();
        if (debug) qDebug() << PDEBUG << ":" << "Desktop" << desktop;
        ApplicationItem *item = ApplicationItem::fromDesktop(desktop);
        items[item->name()] = item;
    }

    return items;
}


/**
 * @fn getApplicationsOrder
 */
QStringList FavoritesCore::getApplicationsOrder()
{
    if (debug) qDebug() << PDEBUG;

    QStringList order;
    QString fileName = QFileInfo(QDir(desktopPath()), QString("order.conf")).filePath();
    if (debug) qDebug() << PDEBUG << ":" << "Configuration file" << fileName;
    QFile configFile(fileName);
    if (!configFile.open(QIODevice::ReadOnly)) return order;

    QString fileStr;
    QStringList value;
    while (true) {
        fileStr = QString(configFile.readLine()).trimmed();
        if ((fileStr.isEmpty()) && (!configFile.atEnd())) continue;
        if ((fileStr[0] == QChar('#')) && (!configFile.atEnd())) continue;
        if ((fileStr[0] == QChar(';')) && (!configFile.atEnd())) continue;
        if (!fileStr.isEmpty()) order.append(fileStr);
        if (configFile.atEnd()) break;
    }
    configFile.close();

    return order;
}
