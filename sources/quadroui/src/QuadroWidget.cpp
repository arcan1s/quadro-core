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
 * @file QuadroWidget.cpp
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadroui/QuadroUi.h"

#include <QApplication>
#include <QPainter>
#include <QShortcut>
#include <QStyleOption>

#include <flowlayout/flowlayout.h>
#include <quadrocore/Quadro.h>

using namespace Quadro;


/**
 * @class QuadroWidget
 */
/**
 * @fn QuadroWidget
 */
QuadroWidget::QuadroWidget(QWidget *_parent, const int _grid,
                           const QString _widgetTitle,
                           const Qt::ScrollBarPolicy _hPolicy,
                           const Qt::ScrollBarPolicy _vPolicy)
    : QScrollArea(_parent)
    , m_grid(_grid)
    , m_title(_widgetTitle)
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;

    setContentsMargins(0, 0, 0, 0);
    setHorizontalScrollBarPolicy(_hPolicy);
    setVerticalScrollBarPolicy(_vPolicy);
    setWidgetResizable(true);

    createObjects();
    createActions();
}


/**
 * @fn ~QuadroWidget
 */
QuadroWidget::~QuadroWidget()
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;

    delete m_widget;
}


/**
 * @fn clearLayout
 */
void QuadroWidget::clearLayout()
{
    QLayoutItem *item;
    while ((item = m_widget->layout()->takeAt(0))) {
        item->widget()->deleteLater();
        delete item;
    }

    setFocus();
}


/**
 * @fn grid
 */
int QuadroWidget::grid() const
{
    return m_grid;
}


/**
 * @fn title
 */
QString QuadroWidget::title() const
{
    return m_title;
}


/**
 * @fn widget
 */
QWidget *QuadroWidget::widget()
{
    return m_widget;
}


/**
 * @fn focusInEvent
 */
void QuadroWidget::focusInEvent(QFocusEvent *_event)
{
    Q_UNUSED(_event);

    return resetFocus();
}


/**
 * @fn paintEvent
 */
void QuadroWidget::paintEvent(QPaintEvent *_event)
{
    QStyleOption options;
    options.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &options, &painter, this);
}


/**
 * @fn moveFocus
 */
void QuadroWidget::moveFocus(const int _dx, const int _dy)
{
    // the idea of the method copied from here
    // http://stackoverflow.com/questions/20856518/navigate-between-widgets-using-arrows-in-qt
    if (!qApp->focusWidget())
        return;
    qCDebug(LOG_UILIB) << "Move to dx" << _dx << "dy" << _dy;

    int index = m_layout->indexOf(qApp->focusWidget());
    if (index == -1)
        return;
    qCInfo(LOG_UILIB) << "Found item with index" << index;

    // get difference between current and new position
    int requestedDiff = _dx * 1 + _dy * stringItemCount();
    int newIndex = [this](const int index, const int requested) {
        int newIndex = index + requested;
        if (newIndex < 0)
            return 0;
        else if (newIndex > m_layout->count())
            return m_layout->count() - 1;
        else
            return newIndex;
    }(index, requestedDiff);

    // this call should never fail because already checked
    QLayoutItem *layoutItem = m_layout->itemAt(newIndex);
    if (!layoutItem)
        return;

    layoutItem->widget()->setFocus();
    return ensureWidgetVisible(layoutItem->widget());
}


/**
 * @fn moveFocusDown
 */
void QuadroWidget::moveFocusDown()
{
    return moveFocus(0, 1);
}


/**
 * @fn moveFocusLeft
 */
void QuadroWidget::moveFocusLeft()
{
    return moveFocus(-1, 0);
}


/**
 * @fn moveFocusRight
 */
void QuadroWidget::moveFocusRight()
{
    return moveFocus(1, 0);
}


/**
 * @fn moveFocusUp
 */
void QuadroWidget::moveFocusUp()
{
    return moveFocus(0, -1);
}


/**
 * @fn resetFocus
 */
void QuadroWidget::resetFocus()
{
    if (m_layout->count() == 0)
        return;
    m_layout->itemAt(0)->widget()->setFocus();
}


/**
 * @fn createActions
 */
void QuadroWidget::createActions()
{
    new QShortcut(QKeySequence(Qt::Key_Down), this, SLOT(moveFocusDown()));
    new QShortcut(QKeySequence(Qt::Key_Left), this, SLOT(moveFocusLeft()));
    new QShortcut(QKeySequence(Qt::Key_Right), this, SLOT(moveFocusRight()));
    new QShortcut(QKeySequence(Qt::Key_Up), this, SLOT(moveFocusUp()));
}


/**
 * @fn createObjects
 */
void QuadroWidget::createObjects()
{
    m_widget = new QWidget(this);
    m_widget->setContentsMargins(0, 0, 0, 0);
    m_layout = new FlowLayout(m_widget);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_widget->setLayout(m_layout);
    setWidget(m_widget);
}


/**
 * @fn stringItemCount
 */
int QuadroWidget::stringItemCount() const
{
    // get margins
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    // calculate effective available space
    QRect effectiveRect
        = m_layout->geometry().adjusted(+left, +top, -right, -bottom);
    int width = effectiveRect.width();

    return width / m_grid;
}
