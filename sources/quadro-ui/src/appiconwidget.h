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


#ifndef APPICONWIDGET_H
#define APPICONWIDGET_H

#include "iconwidget.h"
#include "quadro/quadro.h"


class QMenu;

class AppIconWidget : public IconWidget
{
    Q_OBJECT

public:
    explicit AppIconWidget(ApplicationItem *appItem, const QSize size,
                           QWidget *parent);
    virtual ~AppIconWidget();
    ApplicationItem *associatedItem();

public slots:
    void showContextMenu(const QPoint &pos);

protected:
    void mousePressEvent(QMouseEvent *event);

private slots:
    void addItemToFavorites();
    void editApplication();
    void hideApplication();
    void run();
    void runInNewTab();

private:
    ApplicationItem *m_item = nullptr;
    QMenu *m_menu = nullptr;
    // methods
    void createActions();
};


#endif /* APPICONWIDGET_H */
