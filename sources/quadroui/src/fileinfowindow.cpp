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
 * @file fileinfowindow.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadroui/quadroui.h"
#include "ui_fileinfowindow.h"

#include <quadrocore/quadro.h>


/**
 * @class FileInfoWindow
 */
/**
 * @fn FileInfoWindow
 */
FileInfoWindow::FileInfoWindow(QWidget *parent, QFileInfo item)
    : QDialog(parent)
    , m_item(item)
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;

    ui = new Ui::FileInfoWindow;
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}


/**
 * @fn ~FileInfoWindow
 */
FileInfoWindow::~FileInfoWindow()
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;

    delete ui;
}


/**
 * @fn showWindow
 */
void FileInfoWindow::showWindow()
{
    // set values
    // main
    ui->label_icon->setPixmap(getIcon().pixmap(100, 100));
    ui->label_name->setText(m_item.fileName());
    ui->label_typeData->setText(getMime());
    ui->label_pathData->setText(m_item.absolutePath());

    // size
    QString sizeStr;
    if (m_item.totalSize() > 1024 * 1014 * 1024)
        sizeStr = tr("%1 GiB").arg(
            m_item.totalSize() / (1024.0 * 1014.0 * 1024.0), 0, 'f', 2);
    else if (m_item.totalSize() > 1024 * 1014)
        sizeStr = tr("%1 MiB").arg(m_item.totalSize() / (1024.0 * 1024.0), 0,
                                   'f', 2);
    else if (m_item.totalSize() > 1024)
        sizeStr = tr("%1 KiB").arg(m_item.totalSize() / (1024.0), 0, 'f', 2);
    else
        sizeStr = tr("%1 B").arg(m_item.totalSize());
    if (m_item.isFile())
        ui->label_sizeData->setText(sizeStr);
    else
        ui->label_sizeData->setText(tr("%1 (files %2, directories %3)")
                                        .arg(sizeStr)
                                        .arg(m_item.childFiles())
                                        .arg(m_item.childDirectories()));

    // times
    ui->label_createdData->setText(m_item.created().toString());
    ui->label_modifiedData->setText(m_item.lastModified().toString());
    ui->label_accessData->setText(m_item.lastRead().toString());

    // owner & group
    ui->label_ownerData->setText(m_item.owner());
    ui->label_groupData->setText(m_item.group());

    // rights
    // we are using simplified version. The same system is used in the KDE
    // owner
    if (m_item.permission(QFile::ReadOwner | QFile::WriteOwner))
        ui->label_rOwnerData->setText(tr("read and write"));
    else if (m_item.permission(QFile::ReadOwner))
        ui->label_rOwnerData->setText(tr("read"));
    else
        ui->label_rOwnerData->setText(tr("no rights"));
    // group
    if (m_item.permission(QFile::ReadGroup | QFile::WriteGroup))
        ui->label_rGroupData->setText(tr("read and write"));
    else if (m_item.permission(QFile::ReadGroup))
        ui->label_rGroupData->setText(tr("read"));
    else
        ui->label_rGroupData->setText(tr("no rights"));
    // world
    if (m_item.permission(QFile::ReadOther | QFile::WriteOther))
        ui->label_rWorldData->setText(tr("read and write"));
    else if (m_item.permission(QFile::ReadOther))
        ui->label_rWorldData->setText(tr("read"));
    else
        ui->label_rWorldData->setText(tr("no rights"));
    // exec
    if (m_item.isExecutable())
        ui->checkBox_rExe->setChecked(true);

    open();
}


/**
 * @fn getIcon
 */
QIcon FileInfoWindow::getIcon() const
{
    QVariantList res = DBusOperations::sendRequestToLibrary(
        QString("Icon"), QVariantList() << m_item.absoluteFilePath());
    if (res.isEmpty())
        return QIcon::fromTheme(QString("system-run"));
    else
        return QIcon::fromTheme(res.at(0).toString());
}


/**
 * @fn getMime
 */
QString FileInfoWindow::getMime() const
{
    QVariantList res = DBusOperations::sendRequestToLibrary(
        QString("MIME"), QVariantList() << m_item.absoluteFilePath());

    if (res.isEmpty())
        return QString("other");
    else
        return res.at(0).toString();
}
