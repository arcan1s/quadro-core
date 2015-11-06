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
 * @file fileiconwidget.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef FILEICONWIDGET_H
#define FILEICONWIDGET_H

#include <QFileInfo>

#include "iconwidget.h"


/**
 * @brief The FileIconWidget class provides file UI representation
 */
class FileIconWidget : public IconWidget
{
    Q_OBJECT

public:
    /**
     * @brief FileIconWidget class constructor
     * @param info           associated QFileInfo object
     * @param icon           icon from icon provider
     * @param size           item size
     * @param parent         pointer to parent object
     */
    explicit FileIconWidget(const QFileInfo info, const QIcon icon,
                            const QSize size, QWidget *parent);
    /**
     * @brief FileIconWidget class destructor
     */
    virtual ~FileIconWidget();

public slots:
    /**
     * @brief method which will be called on context menu request
     * @param _pos           current mouse position
     */
    void showContextMenu(const QPoint &_pos) {};

signals:
    /**
     * @brief signal which will be emitted when item will be activated
     * @param _info          associated QFileInfo object
     */
    void openFile(const QFileInfo _info) const;

private:
    /**
     * @brief associated QFileInfo object
     */
    QFileInfo m_info;
};


#endif /* FILEICONWIDGET_H */
