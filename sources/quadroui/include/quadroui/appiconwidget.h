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
 * @file appiconwidget.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef APPICONWIDGET_H
#define APPICONWIDGET_H

#include "iconwidget.h"


class ApplicationItem;
class QMenu;

/**
 * @brief The AppIconWidget class provides application UI representation
 */
class AppIconWidget : public IconWidget
{
    Q_OBJECT

public:
    /**
     * @brief AppIconWidget class constructor
     * @param appItem        pointer to ApplicationItem
     * @param size           item size
     * @param parent         pointer to parent object
     */
    explicit AppIconWidget(ApplicationItem *appItem, const QSize size,
                           QWidget *parent = nullptr);
    /**
     * @brief AppIconWidget class destructor
     */
    virtual ~AppIconWidget();
    /**
     * @brief associated ApplicationItem object
     * @return pointer to ApplicationItem object
     */
    ApplicationItem *associatedItem();

public slots:
    /**
     * @brief method which will be called on context menu request
     * @param _pos           current mouse position
     */
    void showContextMenu(const QPoint &_pos);

protected:
    /**
     * @brief method which will be called on mouse event
     * @param _event         pointer to mouse event
     */
    void mousePressEvent(QMouseEvent *_event);

private slots:
    /**
     * @brief add associated application to favorites
     */
    void addItemToFavorites();
    /**
     * @brief edit associated application
     */
    void editApplication();
    /**
     * @brief hide associated application from launchers
     */
    void hideApplication();
    /**
     * @brief run associated application detached
     */
    void run();
    /**
     * @brief run associated application in new tab
     */
    void runInNewTab();
    /**
     * @brief set files
     */
    void setFiles();
    /**
     * @brief set urls
     */
    void setUrls();

private:
    /**
     * @brief associated ApplicationItem item
     */
    ApplicationItem *m_item = nullptr;
    /**
     * @brief contextual menu
     */
    QMenu *m_menu = nullptr;
    /**
     * @brief command line arguments
     */
    QVariantHash m_args;
    // methods
    /**
     * @brief object create actions
     */
    void createActions();
};


#endif /* APPICONWIDGET_H */
