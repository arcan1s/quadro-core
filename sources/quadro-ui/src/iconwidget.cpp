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

#include <QDebug>
#include <QIcon>
#include <QLabel>
#include <QVBoxLayout>

#include <pdebug/pdebug.h>


IconWidget::IconWidget(ApplicationItem *appItem, const QSize size,
                       QWidget *parent, const bool debugCmd)
    : QWidget(parent),
      debug(debugCmd),
      item(appItem)
{
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
}


IconWidget::~IconWidget()
{
    if (debug) qDebug() << PDEBUG;

    QLayoutItem *item;
    while ((item = layout()->takeAt(0))) {
        delete item->widget();
        delete item;
    }
}


ApplicationItem *IconWidget::associatedItem()
{
    if (debug) qDebug() << PDEBUG;

    return item;
}


void IconWidget::mousePressEvent(QMouseEvent* event)
{
    if (debug) qDebug() << PDEBUG;

    if (event->button() == Qt::LeftButton) {
        if (item->launch()) emit(widgetPressed());
    }
    QWidget::mousePressEvent(event);
}


QSize IconWidget::convertSize(const QSize size)
{
    if (debug) qDebug() << PDEBUG;

    return QSize(size.width() * 0.75, size.height() * 0.75);
}

