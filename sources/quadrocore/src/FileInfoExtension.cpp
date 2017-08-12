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
 * @file FileInfoExtension.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadrocore/Quadro.h"

#include <QDirIterator>

using namespace Quadro;


/**
 * @class FileInfoExtension
 */
/**
 * @fn FileInfoExtension
 */
FileInfoExtension::FileInfoExtension(QFileInfo _base)
    : QFileInfo(_base)
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;

    initMetadata();
}


/**
 * @fn ~FileInfoExtension
 */
FileInfoExtension::~FileInfoExtension()
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;
}


/**
 * @fn childDirectories
 */
long FileInfoExtension::childDirectories() const
{
    return m_childDirectories;
}


/**
 * @fn childFiles
 */
long FileInfoExtension::childFiles() const
{
    return m_childFiles;
}


/**
 * @fn totalSize
 */
long long FileInfoExtension::totalSize() const
{
    return m_totalSize;
}


/**
 * @fn initMetadata
 */
void FileInfoExtension::initMetadata()
{
    // if it is just a file
    if (isFile()) {
        m_totalSize = size();
        return;
    }

    // if it is a directory
    QDirIterator it(absoluteFilePath(),
                    QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden,
                    QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();
        QFileInfo item = it.fileInfo();
        if (item.isDir()) {
            m_childDirectories++;
        } else {
            m_totalSize += item.size();
            m_childFiles++;
        }
    }
}
