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
 * @file fileinfoextension.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef FILEINFOEXTENSION_H
#define FILEINFOEXTENSION_H

#include <QFileInfo>


/**
 * @brief The FileInfoExtension class provides extensions to default QFileInfo
 * class
 */
class FileInfoExtension : public QFileInfo
{
public:
    /**
     * @brief FileInfoExtension class constructor
     * @param base           original QFileInfo item
     */
    FileInfoExtension(QFileInfo base);
    /**
     * @brief FileManager class destructor
     */
    virtual ~FileInfoExtension();
    /**
     * @brief child directories count
     * @return count of child directories
     */
    long childDirectories() const;
    /**
     * @brief child files count
     * @return count of child files
     */
    long childFiles() const;
    /**
     * @brief total child size
     * @return total size including child items in bytes
     */
    long long totalSize() const;

private:
    // properties
    /**
     * @brief child directories count
     */
    long m_childDirectories = 0;
    /**
     * @brief child files count
     */
    long m_childFiles = 0;
    /**
     * @brief total content size in bytes including child directories
     */
    long long m_totalSize = 0;
    // methods
    /**
     * @brief init main metadata
     */
    void initMetadata();
};


#endif /* FILEINFOEXTENSION_H */
