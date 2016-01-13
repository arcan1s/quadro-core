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


class QMenu;

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
     * @brief FileIconWidget class constructor
     * @param path           associated file path
     * @param icon           icon name
     * @param size           item size
     * @param parent         pointer to parent object
     */
    explicit FileIconWidget(const QString path, const QString icon,
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
    void showContextMenu(const QPoint &_pos);

signals:
    /**
     * @brief signal which will be emitted when item will be activated
     * @param _info          associated QFileInfo object
     */
    void openFile(const QFileInfo _info) const;
    /**
     * @brief signal which will be emitted when opening directory in the new
     * tab will be requested
     * @param _info          associated QFileInfo object
     */
    void openDirInNewTab(const QFileInfo _info) const;

protected:
    /**
     * @brief method which will be called on key press event
     * @param _pressedKey    pointer to pressed key
     */
    void keyPressEvent(QKeyEvent *_pressedKey);
    /**
     * @brief method which will be called on mouse event
     * @param _event         pointer to mouse event
     */
    void mousePressEvent(QMouseEvent *_event);

private slots:
    /**
     * @brief additional slot to handle open requests
     */
    void openInNewTabRequested() const;
    /**
     * @brief additional slot to handle open requests
     */
    void openRequested() const;
    /**
     * @brief slot which will be called on entry properties request
     */
    void showProperties();

private:
    /**
     * @brief associated QFileInfo object
     */
    QFileInfo m_info;
    /**
     * @brief contextual menu
     */
    QMenu *m_menu = nullptr;
    // methods
    /**
     * @brief object create actions
     */
    void createActions();
};


#endif /* FILEICONWIDGET_H */
