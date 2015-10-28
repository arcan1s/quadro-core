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


#include "iconwidget.h"

#include <QIcon>
#include <QKeyEvent>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QVBoxLayout>


IconWidget::IconWidget(ApplicationItem *appItem, const QSize size,
                       QWidget *parent)
    : QWidget(parent),
      item(appItem)
{
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;

    setFixedSize(size);
    setLayout(new QVBoxLayout(this));
    // icon
    QLabel *iconLabel = new QLabel(this);
    iconLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    iconLabel->setPixmap(item->icon().pixmap(convertSize(size)));
    layout()->addWidget(iconLabel);
    // text
    QLabel *textLabel = new QLabel(item->name(), this);
    textLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    textLabel->setWordWrap(true);
    layout()->addWidget(textLabel);

    // FIXME temporary line
    setStyleSheet("IconWidget:focus { background: black; color: white; }");
}


IconWidget::~IconWidget()
{
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;

    QLayoutItem *item;
    while ((item = layout()->takeAt(0))) {
        delete item->widget();
        delete item;
    }
}


ApplicationItem *IconWidget::associatedItem()
{
    return item;
}


void IconWidget::keyPressEvent(QKeyEvent *pressedKey)
{
    if ((pressedKey->key() == Qt::Key_Enter)
        || (pressedKey->key() == Qt::Key_Return)){
        if (item->launch()) emit(widgetPressed());
    }
    QWidget::keyPressEvent(pressedKey);
}


void IconWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        if (item->launch()) emit(widgetPressed());
    }
    QWidget::mousePressEvent(event);
}


void IconWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption options;
    options.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &options, &painter, this);
}


QSize IconWidget::convertSize(const QSize size)
{
    return QSize(size.width() * 0.75, size.height() * 0.75);
}

