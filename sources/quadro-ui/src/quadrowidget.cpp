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


#include "quadrowidget.h"

#include <QApplication>
#include <QPainter>
#include <QShortcut>
#include <QStyleOption>

#include <flowlayout/flowlayout.h>

#include "quadro/quadrodebug.h"


QuadroWidget::QuadroWidget(QWidget *parent, const float grid,
                           const Qt::ScrollBarPolicy hPolicy,
                           const Qt::ScrollBarPolicy vPolicy)
    : QScrollArea(parent)
    , m_grid(grid)
{
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;

    setHorizontalScrollBarPolicy(hPolicy);
    setVerticalScrollBarPolicy(vPolicy);
    setWidgetResizable(true);

    createObjects();
    createActions();
}


QuadroWidget::~QuadroWidget()
{
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;

    delete m_widget;
}


QWidget *QuadroWidget::widget()
{
    return m_widget;
}


void QuadroWidget::focusInEvent(QFocusEvent *event)
{
    Q_UNUSED(event);

    return resetFocus();
}


void QuadroWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption options;
    options.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &options, &painter, this);
}


void QuadroWidget::moveFocus(const int dx, const int dy)
{
    // the idea of the method copied from here
    // http://stackoverflow.com/questions/20856518/navigate-between-widgets-using-arrows-in-qt
    if(qApp->focusWidget() == nullptr)
        return;
    qCDebug(LOG_UI) << "Move to dx" << dx << "dy" << dy;

    int index = m_layout->indexOf(qApp->focusWidget());
    if(index == -1)
        return;
    qCInfo(LOG_UI) << "Found item with index" << index;

    // get difference between current and new position
    int requestedDiff = dx * 1 + dy * stringItemCount();
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
    if (layoutItem == nullptr)
        return;

    layoutItem->widget()->setFocus();
    return ensureWidgetVisible(layoutItem->widget());
}


void QuadroWidget::moveFocusDown()
{
    return moveFocus(0, 1);
}


void QuadroWidget::moveFocusLeft()
{
    return moveFocus(-1, 0);
}


void QuadroWidget::moveFocusRight()
{
    return moveFocus(1, 0);
}


void QuadroWidget::moveFocusUp()
{
    return moveFocus(0, -1);
}


void QuadroWidget::resetFocus()
{
    if (m_layout->count() == 0)
        return;
    m_layout->itemAt(0)->widget()->setFocus();
}


void QuadroWidget::createActions()
{
    QShortcut *shortcut;
    shortcut = new QShortcut(QKeySequence(Qt::Key_Down), this,
                             SLOT(moveFocusDown()));
    shortcut = new QShortcut(QKeySequence(Qt::Key_Left), this,
                             SLOT(moveFocusLeft()));
    shortcut = new QShortcut(QKeySequence(Qt::Key_Right), this,
                             SLOT(moveFocusRight()));
    shortcut = new QShortcut(QKeySequence(Qt::Key_Up), this,
                             SLOT(moveFocusUp()));
}


void QuadroWidget::createObjects()
{
    m_widget = new QWidget(this);
    m_layout = new FlowLayout(m_widget);
    m_widget->setLayout(m_layout);
    setWidget(m_widget);
}


int QuadroWidget::stringItemCount() const
{
    // get margins
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    // calculate effective availble space
    QRect effectiveRect =  m_layout->geometry().adjusted(+left, +top, -right, -bottom);
    int width = effectiveRect.width();

    return static_cast<int>(width / m_grid);
}
