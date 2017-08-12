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
 * @file fileinfowindow.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef FILEINFOWINDOW_H
#define FILEINFOWINDOW_H

#include <QDialog>

#include <quadrocore/fileinfoextension.h>


namespace Ui
{
class FileInfoWindow;
}

/**
 * @brief The FileInfoWindow class provides dialog to show entry data
 */
class FileInfoWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief FileInfoWindow class constructor
     * @param _parent pointer to parent object
     * @param _item object information
     */
    explicit FileInfoWindow(QWidget *_parent, const QFileInfo _item);
    /**
     * @brief FileInfoWindow class destructor
     */
    virtual ~FileInfoWindow();

public slots:
    /**
     * @brief method which will be called to show window
     */
    void showWindow();

private:
    // ui
    /**
     * @brief pointer to ui object
     */
    Ui::FileInfoWindow *ui = nullptr;
    // backend
    /**
     * @brief object information
     */
    FileInfoExtension m_item;
    // methods
    /**
     * @brief get icon using main DBus interface
     * @return icon object
     */
    QIcon getIcon() const;
    /**
     * @brief get MIME name using main DBus interface
     */
    QString getMime() const;
};


#endif /* FileInfoWindow */
