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
 * @file recentlycore.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadrocore/quadro.h"

#include <QDir>
#include <QProcessEnvironment>
#include <QStandardPaths>


/**
 * @class RecentlyCore
 */
/**
 * @fn RecentlyCore
 */
RecentlyCore::RecentlyCore(QObject *parent, const int recentItems)
    : AbstractAppAggregator(parent),
      m_recentItems(recentItems)
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;
}


/**
 * @fn ~RecentlyCore
 */
RecentlyCore::~RecentlyCore()
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;

    m_modifications.clear();
}


/**
 * @fn applicationsBySubstr
 */
QMap<QString, ApplicationItem *> RecentlyCore::applicationsBySubstr(const QString _substr) const
{
    qCDebug(LOG_LIB) << "Substring" << _substr;

    QMap<QString, ApplicationItem *> apps;
    foreach (const QString app, applications().keys()) {
        if (!applications()[app]->startsWith(_substr)) continue;
        apps[app] = applications()[app];
    }

    return apps;
}


/**
 * @fn desktopPath
 */
QString RecentlyCore::desktopPath()
{
    QString homePath = QString("%1/%2").arg(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation))
                                       .arg(HOME_PATH);

    return QString("%1/%2").arg(homePath).arg(RECENT_PATH);
}


/**
 * @fn addItem
 */
ApplicationItem *RecentlyCore::addItem(ApplicationItem *_item)
{
    qCDebug(LOG_LIB) << "Item name" << _item->name();

    rotate();
    QDateTime modification = QDateTime::currentDateTime();

    _item->setComment(modification.toString(Qt::ISODate));
    _item->setIcon(QString("emblem-favorites"));

    if (_item->saveDesktop(desktopPath()).isEmpty()) {
        qCCritical(LOG_LIB) << "Could not save" << _item->desktopName();
        return nullptr;
    }
    initApplications();

    return _item;
}


/**
 * @fn addItem
 */
ApplicationItem *RecentlyCore::addItem(const QString _name)
{
    qCDebug(LOG_LIB) << "Item name" << _name;

    ApplicationItem *item = new ApplicationItem(this, _name);
    item->setExec(_name);

    return addItem(item);
}


/**
 * @fn initApplications
 */
void RecentlyCore::initApplications()
{
    // start cleanup
    dropApplications();
    m_modifications.clear();

    QMap<QString, ApplicationItem *> desktops = getApplicationsFromDesktops();
    foreach (const QString desktop, desktops.keys())
        addApplication(desktops[desktop]);

    // cleanup
    desktops.clear();
}


/**
 * @fn removeItemByName
 */
void RecentlyCore::removeItemByName(const QString _name)
{
    qCDebug(LOG_LIB) << "Item name" << _name;

    if (!hasApplication(_name)) {
        qCCritical(LOG_LIB) << "Invalid item" << _name;
        return;
    }

    QFile desktop(QString("%1/%2").arg(desktopPath()).arg(applications()[_name]->desktopName()));
    if (!desktop.remove()) {
        qCCritical(LOG_LIB) << "Could not remove" << desktop.fileName();
        return;
    }

    initApplications();
}


/**
 * @fn touchItem
 */
void RecentlyCore::touchItem(const QString _name)
{
    qCDebug(LOG_LIB) << "Item" << _name;

    // TODO rewrite to use Comment field
    if (!hasApplication(_name)) {
        qCCritical(LOG_LIB) << "Invalid item" << _name;
        return;
    }

    QDateTime modification = QDateTime::currentDateTime();
    applications()[_name]->setComment(modification.toString(Qt::ISODate));

    applications()[_name]->saveDesktop(desktopPath());
    m_modifications[_name] = modification;
}


/**
 * @fn getApplicationsFromDesktops
 */
QMap<QString, ApplicationItem *> RecentlyCore::getApplicationsFromDesktops()
{
    QStringList filter("*.desktop");
    QMap<QString, ApplicationItem *> items;

    QStringList entries = QDir(desktopPath()).entryList(filter, QDir::Files);
    foreach (const QString entry, entries) {
        QString desktop = QFileInfo(QDir(desktopPath()), entry).filePath();
        qCInfo(LOG_LIB) << ":" << "Desktop" << desktop;
        ApplicationItem *item = ApplicationItem::fromDesktop(desktop, this);
        items[item->name()] = item;
        m_modifications[item->name()] = QFileInfo(QDir(desktopPath()), entry).lastModified();
    }

    return items;
}


/**
 * @fn rotate
 */
void RecentlyCore::rotate()
{
    if (applications().count() <= m_recentItems) {
        qCInfo(LOG_LIB) << "Nothing to do here";
        return;
    }

    QString lastKey;
    QDateTime lastTime = QDateTime::currentDateTime();
    foreach (const QString app, m_modifications.keys()) {
        if (m_modifications[app] >= lastTime) continue;
        lastKey = app;
        lastTime = m_modifications[app];
    }
    if (lastKey.isEmpty()) {
        qCCritical(LOG_LIB) << "Could not find item to rotate, WTF?";
        return;
    }

    removeItemByName(lastKey);
}
