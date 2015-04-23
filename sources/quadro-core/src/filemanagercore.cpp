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


#include <QDebug>
#include <QDesktopServices>
#include <QDir>
#include <QMimeDatabase>
#include <QUrl>

#include <quadro/quadro.h>
#include <pdebug/pdebug.h>


/**
 * @class FileManager
 */
/**
 * @fn FileManager
 */
FileManager::FileManager(QObject *parent, const bool debugCmd)
    : QObject(parent),
      debug(debugCmd)
{
}


/**
 * @fn ~FileManager
 */
FileManager::~FileManager()
{
    if (debug) qDebug() << PDEBUG;
}


/**
 * @fn directoryEntries
 */
QFileInfoList FileManager::directoryEntries(const QString _directory, const bool _hidden,
                                            const QStringList _filter)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Directory" << _directory;
    if (debug) qDebug() << PDEBUG << ":" << "Show hidden" << _hidden;
    if (debug) qDebug() << PDEBUG << ":" << "Filter" << _filter;

    QDir dir = QDir(_directory);
    if (!dir.exists()) {
        if (debug) qDebug() << PDEBUG << ":" << "Could not find directory";
        return QFileInfoList();
    }

    if (_hidden)
        return dir.entryInfoList(_filter, QDir::AllEntries | QDir::Hidden | QDir::NoDotAndDotDot);
    else
        return dir.entryInfoList(_filter, QDir::AllEntries | QDir::NoDotAndDotDot);
}


/**
 * @fn iconByFileName
 */
QIcon FileManager::iconByFileName(const QString _file)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "File" << _file;

    QString iconName = mimeByFileName(_file).iconName();
    if (debug) qDebug() << PDEBUG << ":" << "Icon name" << iconName;

    return QIcon::fromTheme(iconName);
}


/**
 * @fn mimeTypeForFile
 */
QMimeType FileManager::mimeByFileName(const QString _file)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "File" << _file;

    QMimeDatabase database;
    QMimeType type = database.mimeTypeForFile(_file);
    if (debug) qDebug() << PDEBUG << ":" << "Mime type" << type.name();

    return type;
}


/**
 * @fn
 */
bool FileManager::openFile(const QFileInfo _file)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "File" << _file.absoluteFilePath();

    QUrl url = QUrl::fromLocalFile(_file.absoluteFilePath());

    return QDesktopServices::openUrl(url);
}
