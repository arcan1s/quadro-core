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


#ifndef ICONWIDGET_H
#define ICONWIDGET_H

#include <QSize>
#include <QWidget>


class QIcon;
class QKeyEvent;
class QLabel;
class QMouseEvent;

class IconWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IconWidget(const QSize size, QWidget *parent);
    virtual ~IconWidget();
    inline QSize convertSize(const QSize size);
    void setIcon(const QIcon icon);
    void setText(const QString text);

public slots:
    virtual void showContextMenu(const QPoint &pos) = 0;

signals:
    void widgetPressed();

protected:
    void keyPressEvent(QKeyEvent *pressedKey);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    // ui
    QLabel *m_iconLabel = nullptr;
    QLabel *m_textLabel = nullptr;
    // properties
    QSize m_size;
};


#endif /* ICONWIDGET_H */
