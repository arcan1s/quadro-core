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
 * @file filemanagercore.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadro/quadro.h"

#include <QDesktopServices>
#include <QDir>
#include <QIcon>
#include <QMimeDatabase>
#include <QMimeType>
#include <QUrl>


/**
 * @class FileManagerCore
 */
/**
 * @fn FileManagerCore
 */
FileManagerCore::FileManagerCore(QObject *parent)
    : QObject(parent)
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;
}


/**
 * @fn ~FileManagerCore
 */
FileManagerCore::~FileManagerCore()
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;
}


/**
 * @fn directoryEntries
 */
QFileInfoList FileManagerCore::directoryEntries(const QString _directory, const bool _hidden,
                                                const QStringList _filter) const
{
    qCDebug(LOG_LIB) << "Directory" << _directory;
    qCDebug(LOG_LIB) << "Show hidden" << _hidden;
    qCDebug(LOG_LIB) << "Filter" << _filter;

    QDir dir = QDir(_directory);
    if (!dir.exists()) {
        qCCritical(LOG_LIB) << "Could not find directory" << _directory;
        return QFileInfoList();
    }

    if (_hidden)
        return dir.entryInfoList(_filter, QDir::AllEntries | QDir::Hidden | QDir::NoDot);
    else
        return dir.entryInfoList(_filter, QDir::AllEntries | QDir::NoDot);
}


/**
 * @fn iconByFileName
 */
QIcon FileManagerCore::iconByFileName(const QString _file) const
{
    qCDebug(LOG_LIB) << "File" << _file;

    QString iconName = mimeByFileName(_file).iconName();
    qCDebug(LOG_LIB) << "Icon name" << iconName;

    return QIcon::fromTheme(iconName);
}


/**
 * @fn mimeTypeForFile
 */
QMimeType FileManagerCore::mimeByFileName(const QString _file) const
{
    qCDebug(LOG_LIB) << "File" << _file;

    QMimeDatabase database;
    QMimeType type = database.mimeTypeForFile(_file);
    qCDebug(LOG_LIB) << "Mime type" << type.name();

    return type;
}


/**
 * @fn
 */
bool FileManagerCore::openFile(const QFileInfo _file) const
{
    qCDebug(LOG_LIB) << "File" << _file.absoluteFilePath();

    QUrl url = QUrl::fromLocalFile(_file.absoluteFilePath());

    return QDesktopServices::openUrl(url);
}
