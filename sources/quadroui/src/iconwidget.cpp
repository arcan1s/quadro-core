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
 * @file iconwidget.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadroui/quadroui.h"

#include <QIcon>
#include <QKeyEvent>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QVBoxLayout>

#include <quadrocore/quadro.h>


/**
 * @class IconWidget
 */
/**
 * @fn IconWidget
 */
IconWidget::IconWidget(const QSize size, QWidget *parent)
    : QWidget(parent)
    , m_size(size)
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;

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


/**
 * @fn ~IconWidget
 */
IconWidget::~IconWidget()
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;

    delete m_iconLabel;
    delete m_textLabel;
}


/**
 * @fn convertSize
 */
QSize IconWidget::convertSize(const QSize _size) const
{
    return QSize(_size.width() * 0.75, _size.height() * 0.75);
}


/**
 * @fn setIcon
 */
void IconWidget::setIcon(const QIcon _icon)
{
    qCDebug(LOG_UILIB) << "New icon" << _icon.name();

    m_iconLabel->setPixmap(_icon.pixmap(convertSize(m_size)));
}


/**
 * @fn setText
 */
void IconWidget::setText(const QString _text)
{
    qCDebug(LOG_UILIB) << "New text" << _text;

    m_textLabel->setText(_text);
}


/**
 * @fn keyPressEvent
 */
void IconWidget::keyPressEvent(QKeyEvent *_pressedKey)
{
    if ((_pressedKey->key() == Qt::Key_Enter)
        || (_pressedKey->key() == Qt::Key_Return)) {
        emit(widgetPressed());
    }

    QWidget::keyPressEvent(_pressedKey);
}


/**
 * @fn mousePressEvent
 */
void IconWidget::mousePressEvent(QMouseEvent *_event)
{
    if (_event->button() == Qt::LeftButton) {
        emit(widgetPressed());
    }

    QWidget::mousePressEvent(_event);
}


/**
 * @fn paintEvent
 */
void IconWidget::paintEvent(QPaintEvent *_event)
{
    QStyleOption options;
    options.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &options, &painter, this);
}
