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
 * @file documentscore.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadrocore/quadro.h"

#include <QDir>
#include <QStandardPaths>


/**
 * @class DocumentsCore
 */
/**
 * @fn DocumentsCore
 */
DocumentsCore::DocumentsCore(QObject *_parent, const int _recentItems)
    : AbstractAppAggregator(_parent)
    , m_recentItems(_recentItems)
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;
}


/**
 * @fn ~DocumentsCore
 */
DocumentsCore::~DocumentsCore()
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;
}


/**
 * @fn desktopPath
 */
QString DocumentsCore::desktopPath()
{
    QString homePath = QString("%1/%2")
                           .arg(QStandardPaths::writableLocation(
                               QStandardPaths::GenericDataLocation))
                           .arg(HOME_PATH);

    return QString("%1/%2").arg(homePath).arg(DOCUMENTS_PATH);
}


/**
 * @fn getApplicationsFromDesktops
 */
QMap<QString, ApplicationItem *> DocumentsCore::getApplicationsFromDesktops()
{
    QStringList filter("*.desktop");
    QMap<QString, ApplicationItem *> items;

    QStringList entries
        = QDir(desktopPath()).entryList(filter, QDir::Files, QDir::Time);
    for (auto &entry : entries) {
        QString desktop = QFileInfo(QDir(desktopPath()), entry).filePath();
        qCInfo(LOG_LIB) << "Desktop" << desktop;
        ApplicationItem *item = ApplicationItem::fromDesktop(desktop, this);
        items[item->name()] = item;
        m_modifications.append(item->name());
    }

    return items;
}


/**
 * @fn recent
 */
QStringList DocumentsCore::recent() const
{
    QStringList apps;
    for (auto item : applications())
        apps.append(item->name());

    return apps;
}


/**
 * @fn addItem
 */
ApplicationItem *DocumentsCore::addItem(const QString &_name)
{
    qCDebug(LOG_LIB) << "Item name" << _name;

    rotate();
    QDateTime modification = QDateTime::currentDateTime();

    ApplicationItem *item
        = new ApplicationItem(this, QFileInfo(_name).fileName());
    item->setComment(modification.toString(Qt::ISODate));
    item->setType("Link");
    item->setUrl(QString("file://%1").arg(QFileInfo(_name).absoluteFilePath()));
    // get icon
    QVariantList res = DBusOperations::sendRequestToLibrary(
        "Icon", QVariantList() << QFileInfo(_name).absoluteFilePath());
    if (res.isEmpty())
        item->setIcon("system-run");
    else
        item->setIcon(res.at(0).toString());

    if (item->saveDesktop(desktopPath()).isEmpty()) {
        qCCritical(LOG_LIB) << "Could not save" << item->desktopName();
        return nullptr;
    }
    initApplications();

    item->deleteLater();
    return applications()[QFileInfo(_name).fileName()];
}


/**
 * @fn initApplications
 */
void DocumentsCore::initApplications()
{
    // start cleanup
    dropApplications();
    m_modifications.clear();

    QMap<QString, ApplicationItem *> desktops = getApplicationsFromDesktops();
    for (auto desktop : desktops.values())
        addApplication(desktop);

    // cleanup
    desktops.clear();
}


/**
 * @fn removeItemByName
 */
void DocumentsCore::removeItemByName(const QString &_name)
{
    qCDebug(LOG_LIB) << "Item name" << _name;

    if (!hasApplication(_name)) {
        qCCritical(LOG_LIB) << "Invalid item" << _name;
        return;
    }

    QFile desktop(QString("%1/%2")
                      .arg(desktopPath())
                      .arg(applications()[_name]->desktopName()));
    if (!desktop.remove()) {
        qCCritical(LOG_LIB) << "Could not remove" << desktop.fileName();
        return;
    }

    initApplications();
}


/**
 * @fn touchItem
 */
void DocumentsCore::touchItem(const QString &_name)
{
    qCDebug(LOG_LIB) << "Item" << _name;

    if (!hasApplication(_name)) {
        qCCritical(LOG_LIB) << "Invalid item" << _name;
        return;
    }

    QDateTime modification = QDateTime::currentDateTime();
    applications()[_name]->setComment(modification.toString(Qt::ISODate));

    applications()[_name]->saveDesktop(desktopPath());
    // update order
    int index = m_modifications.indexOf(_name);
    m_modifications.move(index, m_modifications.count() - 1);
}


/**
 * @fn rotate
 */
void DocumentsCore::rotate()
{
    if (applications().count() <= m_recentItems) {
        qCInfo(LOG_LIB) << "Nothing to do here";
        return;
    }

    return removeItemByName(m_modifications.first());
}
