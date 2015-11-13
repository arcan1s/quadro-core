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


#include "quadrocore/quadro.h"

#include <QDir>
#include <QSettings>
#include <QStandardPaths>


/**
 * @class FavoritesCore
 */
/**
 * @fn FavoritesCore
 */
FavoritesCore::FavoritesCore(QObject *parent)
    : QObject(parent)
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;
}


/**
 * @fn ~FavoritesCore
 */
FavoritesCore::~FavoritesCore()
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;

    m_applications.clear();
}


/**
 * @fn add
 */
void FavoritesCore::add(ApplicationItem *_item)
{
    if (check(_item))
        removeAppFromFavorites(_item);
    else
        addAppToFavorites(_item);
}


/**
 * @fn applications
 */
QMap<QString, ApplicationItem *> FavoritesCore::applications() const
{
    return m_applications;
}


/**
 * @fn addToFavorites
 */
ApplicationItem *FavoritesCore::addToFavorites(ApplicationItem *_item)
{
    FavoritesCore *instance = new FavoritesCore(nullptr);
    instance->initApplications();

    instance->add(_item);
    delete instance;

    return _item;
}


/**
 * @fn addToFavorites
 */
ApplicationItem *FavoritesCore::addToFavorites(const QString _executable,
                                               const QString _name,
                                               const QString _iconName)
{
    qCDebug(LOG_LIB) << "Executable" << _executable;
    qCDebug(LOG_LIB) << "Name" << _name;
    qCDebug(LOG_LIB) << "Icon" << _iconName;

    ApplicationItem *item = new ApplicationItem(nullptr, _name);
    item->setExec(_name);
    item->setIcon(_iconName);
    FavoritesCore *instance = new FavoritesCore(nullptr);
    instance->initApplications();

    instance->add(item);
    delete instance;

    return addToFavorites(item);
}


/**
 * @fn check
 */
bool FavoritesCore::check(ApplicationItem *_item)
{
    return m_applications.contains(_item->name());
}


/**
 * @fn desktopPath
 */
QString FavoritesCore::desktopPath()
{
    QString homePath = QString("%1/%2").arg(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation))
                                       .arg(HOME_PATH);

    return QString("%1/%2").arg(homePath).arg(FAVORITES_PATH);
}


/**
 * @fn hasApplication
 */
bool FavoritesCore::hasApplication(ApplicationItem *_item)
{
    FavoritesCore *instance = new FavoritesCore(nullptr);
    instance->initApplications();

    return instance->check(_item);
}


/**
 * @fn order
 */
QStringList FavoritesCore::order() const
{
    return m_order;
}


/**
 * @fn changeApplicationState
 */
void FavoritesCore::changeApplicationState(const QString _name, const bool _up)
{
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
    QString fileName = QFileInfo(QDir(desktopPath()), QString("index.conf")).filePath();
    qCInfo(LOG_LIB) << "Configuration file" << fileName;
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");

    settings.setValue(QString("Order"), m_order);

    settings.sync();
}


/**
 * @fn addAppToFavorites
 */
void FavoritesCore::addAppToFavorites(ApplicationItem *_item)
{
    if (!_item->saveDesktop(desktopPath()).isEmpty()) {
        // update data
        m_applications[_item->name()] = _item;
        m_order.append(_item->name());
        saveApplicationsOrder();
    } else {
        qCWarning(LOG_LIB) << "Could not save item" << _item->name() << "to" << desktopPath();
    }
}


/**
 * @fn getApplicationsFromDesktops
 */
QMap<QString, ApplicationItem *> FavoritesCore::getApplicationsFromDesktops()
{
    QStringList filter("*.desktop");
    QMap<QString, ApplicationItem *> items;

    QStringList entries = QDir(desktopPath()).entryList(filter, QDir::Files);
    for (auto entry : entries) {
        QString desktop = QFileInfo(QDir(desktopPath()), entry).filePath();
        qCInfo(LOG_LIB) << "Desktop" << desktop;
        ApplicationItem *item = ApplicationItem::fromDesktop(desktop, this);
        items[item->name()] = item;
    }

    return items;
}


/**
 * @fn getApplicationsOrder
 */
QStringList FavoritesCore::getApplicationsOrder() const
{
    QString fileName = QFileInfo(QDir(desktopPath()), QString("index.conf")).filePath();
    qCInfo(LOG_LIB) << "Configuration file" << fileName;
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");

    return settings.value(QString("Order")).toStringList();
}


/**
 * @fn removeAppFromFavorites
 */
void FavoritesCore::removeAppFromFavorites(ApplicationItem *_item)
{
    if (_item->removeDesktop(desktopPath())) {
        m_applications.remove(_item->name());
        m_order.removeAll(_item->name());
        saveApplicationsOrder();
    } else {
        qCWarning(LOG_LIB) << "Could not remove item" << _item->name() << "to" << desktopPath();
    }
}
