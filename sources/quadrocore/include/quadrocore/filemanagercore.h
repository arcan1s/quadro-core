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
 * @file filemanagercore.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef FILEMANAGERCORE_H
#define FILEMANAGERCORE_H

#include <QFileInfo>
#include <QObject>


class QIcon;
class QMimeType;

/**
 * @brief The FileManager class provides file manager backend
 */
class FileManagerCore : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief FileManager class constructor
     * @param parent         pointer to parent item
     */
    explicit FileManagerCore(QObject *parent);
    /**
     * @brief FileManager class destructor
     */
    virtual ~FileManagerCore();
    /**
     * @brief find directory entries
     * @param _directory     path to directory on which you are looking for
     * @param _hidden        show hidden files or not
     * @param _filter        name filter
     * @return list of files
     */
    QFileInfoList directoryEntries(const QString _directory,
                                   const bool _hidden = false,
                                   const QStringList _filter = QStringList()) const;
    /**
     * @brief find entries by substring
     * @param _directory     parent directory
     * @param _substr        substring for name
     * @param _hidden        show hidden files or not
     */
    QFileInfoList entriesBySubstr(const QString _directory, const QString _substr,
                                  const bool _hidden = false) const;
    /**
     * @brief get icon by file name
     * @param _file          path to file
     * @return QIcon of the file
     */
    QIcon iconByFileName(const QString _file) const;
    /**
     * @brief get icon name by file name
     * @param _file          path to file
     * @return icon name
     */
    QString iconNameByFileName(const QString _file) const;
    /**
     * @brief get mime type of given file
     * @param _file          path to file
     * @return QMimeType construction
     */
    QMimeType mimeByFileName(const QString _file) const;

public slots:
    /**
     * @brief open file using XDG
     * @param _file          QFileInfo of given file
     * @return true if opening successfully
     * @return false if an error occurs
     */
    bool openFile(const QFileInfo _file) const;

private:
};


#endif /* FILEMANAGERCORE_H */
