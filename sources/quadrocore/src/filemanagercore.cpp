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


#include "quadrocore/quadro.h"

#include <QDesktopServices>
#include <QDir>
#include <QDirIterator>
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
FileManagerCore::FileManagerCore(QObject *_parent)
    : QObject(_parent)
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
QFileInfoList
FileManagerCore::directoryEntries(const QString &_directory, const bool _hidden,
                                  const QStringList &_filter) const
{
    qCDebug(LOG_LIB) << "Directory" << _directory << "and show hidden"
                     << _hidden << "filter" << _filter;

    QDir dir = QDir(_directory);
    if (!dir.exists()) {
        qCCritical(LOG_LIB) << "Could not find directory" << _directory;
        return QFileInfoList();
    }

    if (_hidden)
        return dir.entryInfoList(_filter,
                                 QDir::AllEntries | QDir::Hidden | QDir::NoDot);
    else
        return dir.entryInfoList(_filter, QDir::AllEntries | QDir::NoDot);
}


/**
 * @fn entriesBySubstr
 */
QFileInfoList FileManagerCore::entriesBySubstr(const QString &_directory,
                                               const QString &_substr,
                                               const bool _hidden) const
{
    qCDebug(LOG_LIB) << "Directory" << _directory << "and show hidden"
                     << _hidden << "substring" << _substr;

    QDir::Filters filters
        = _hidden ? QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden
                  : QDir::AllEntries | QDir::NoDotAndDotDot;
    QFileInfoList foundEntries;

    QDirIterator it(_directory, QStringList({QString("*%1*").arg(_substr)}),
                    filters, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();
        foundEntries.append(it.fileInfo());
    }

    return foundEntries;
}


/**
 * @fn iconByFileName
 */
QIcon FileManagerCore::iconByFileName(const QString &_file) const
{
    qCDebug(LOG_LIB) << "File" << _file;

    return QIcon::fromTheme(iconNameByFileName(_file));
}


/**
 * @fn iconNameByFileName
 */
QString FileManagerCore::iconNameByFileName(const QString &_file) const
{
    qCDebug(LOG_LIB) << "File" << _file;

    return mimeByFileName(_file).iconName();
}


/**
 * @fn mimeTypeForFile
 */
QMimeType FileManagerCore::mimeByFileName(const QString &_file) const
{
    qCDebug(LOG_LIB) << "File" << _file;

    QMimeDatabase database;
    QMimeType type = database.mimeTypeForFile(_file);
    qCDebug(LOG_LIB) << "Mime type" << type.name();

    return type;
}


/**
 * @fn openFile
 */
bool FileManagerCore::openFile(const QFileInfo &_file) const
{
    qCDebug(LOG_LIB) << "File" << _file.absoluteFilePath();

    QUrl url = QUrl::fromLocalFile(_file.absoluteFilePath());

    return QDesktopServices::openUrl(url);
}
