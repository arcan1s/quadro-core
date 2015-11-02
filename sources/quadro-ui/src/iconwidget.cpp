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

#include "quadro/quadrodebug.h"


IconWidget::IconWidget(const QSize size, QWidget *parent)
    : QWidget(parent)
    , m_size(size)
{
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;

    setFixedSize(m_size);
    setLayout(new QVBoxLayout(this));
    // icon
    m_iconLabel = new QLabel(this);
    m_iconLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    layout()->addWidget(m_iconLabel);
    // text
    m_textLabel = new QLabel(this);
    m_textLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_textLabel->setWordWrap(true);
    layout()->addWidget(m_textLabel);

    setMouseTracking(true);

    // context menu
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this,
            SLOT(showContextMenu(const QPoint &)));

    // FIXME temporary line
    setStyleSheet("IconWidget:focus { background: black; color: white; }");
}


IconWidget::~IconWidget()
{
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;

    delete m_iconLabel;
    delete m_textLabel;
}


QSize IconWidget::convertSize(const QSize size)
{
    return QSize(size.width() * 0.75, size.height() * 0.75);
}


void IconWidget::setIcon(const QIcon icon)
{
    m_iconLabel->setPixmap(icon.pixmap(convertSize(m_size)));
}


void IconWidget::setText(const QString text)
{
    m_textLabel->setText(text);
}


void IconWidget::keyPressEvent(QKeyEvent *pressedKey)
{
    if ((pressedKey->key() == Qt::Key_Enter)
        || (pressedKey->key() == Qt::Key_Return)) {
        emit(widgetPressed());
    }
    QWidget::keyPressEvent(pressedKey);
}


void IconWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit(widgetPressed());
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
