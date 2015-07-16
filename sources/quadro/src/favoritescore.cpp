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
#include <QSettings>
#include <QStandardPaths>

#include <quadro/quadro.h>
#include <pdebug/pdebug.h>

#include "version.h"


/**
 * @class FavoritesCore
 */
/**
 * @fn FavoritesCore
 */
FavoritesCore::FavoritesCore(QObject *parent, const bool debugCmd)
    : QObject(parent),
      debug(debugCmd)
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
QMap<QString, ApplicationItem *> FavoritesCore::applications() const
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
    ApplicationItem *item = new ApplicationItem(this, _executable, _name);
    item->setIconByName(_iconName);

    if (!item->saveDesktop(desktopPath()).isEmpty()) {
        delete item;
        item = nullptr;
        // update data
        m_applications[_name] = item;
        m_order.append(_name);
        saveApplicationsOrder();
    }

    return item;
}


/**
 * @fn desktopPath
 */
QString FavoritesCore::desktopPath()
{
    QString homePath = QString("%1/%2").arg(QStandardPaths::writableLocation(QStandardPaths::DataLocation))
                                       .arg(HOME_PATH);

    return QString("%1/%2").arg(homePath).arg(FAVORITES_PATH);
}


/**
 * @fn changeApplicationState
 */
void FavoritesCore::changeApplicationState(const QString _name, const bool _up)
{
    if (debug) qDebug() << PDEBUG;

    int current = m_order.indexOf(_name);
    if (current == -1) return;

    int next = _up ? current - 1 : current + 1;
    if ((next == -1) || (next == m_order.count())) return;

    m_order.swap(current, next);
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
}


/**
 * @fn saveApplicationsOrder
 */
void FavoritesCore::saveApplicationsOrder() const
{
    if (debug) qDebug() << PDEBUG;

    QString fileName = QFileInfo(QDir(desktopPath()), QString("index.conf")).filePath();
    if (debug) qDebug() << PDEBUG << ":" << "Configuration file" << fileName;
    QSettings settings(fileName, QSettings::IniFormat);

    settings.setValue(QString("Order"), m_order);

    settings.sync();
}


/**
 * @fn getApplicationsFromDesktops
 */
QMap<QString, ApplicationItem *> FavoritesCore::getApplicationsFromDesktops()
{
    if (debug) qDebug() << PDEBUG;

    QStringList filter("*.desktop");
    QMap<QString, ApplicationItem *> items;

    QStringList entries = QDir(desktopPath()).entryList(filter, QDir::Files);
    for (int i=0; i<entries.count(); i++) {
        QString desktop = QFileInfo(QDir(desktopPath()), entries[i]).filePath();
        if (debug) qDebug() << PDEBUG << ":" << "Desktop" << desktop;
        ApplicationItem *item = ApplicationItem::fromDesktop(desktop, this, debug);
        items[item->name()] = item;
    }

    return items;
}


/**
 * @fn getApplicationsOrder
 */
QStringList FavoritesCore::getApplicationsOrder() const
{
    if (debug) qDebug() << PDEBUG;

    QString fileName = QFileInfo(QDir(desktopPath()), QString("index.conf")).filePath();
    if (debug) qDebug() << PDEBUG << ":" << "Configuration file" << fileName;
    QSettings settings(fileName, QSettings::IniFormat);

    return settings.value(QString("Order")).toStringList();
}
