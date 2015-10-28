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


#ifndef QUADROWIDGET_H
#define QUADROWIDGET_H

#include <QScrollArea>


class FlowLayout;
class QFocusEvent;

class QuadroWidget : public QScrollArea
{
    Q_OBJECT

public:
    explicit QuadroWidget(QWidget *parent, const float grid,
                          const Qt::ScrollBarPolicy hPolicy = Qt::ScrollBarAlwaysOff,
                          const Qt::ScrollBarPolicy vPolicy = Qt::ScrollBarAsNeeded);
    virtual ~QuadroWidget();
    // override default method
    QWidget *widget();

protected:
    void focusInEvent(QFocusEvent *event);
    void paintEvent(QPaintEvent *event);

public slots:
    void moveFocus(const int dx, const int dy);
    void moveFocusDown();
    void moveFocusLeft();
    void moveFocusRight();
    void moveFocusUp();
    void resetFocus();

private:
    // ui
    FlowLayout *m_layout = nullptr;
    QWidget *m_widget = nullptr;
    // methods
    void createActions();
    void createObjects();
    int stringItemCount() const;
    // properties
    float m_grid = 0;
};


#endif /* QUADROWIDGET_H */
