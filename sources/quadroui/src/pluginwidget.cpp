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
 * @file pluginwidget.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadroui/quadroui.h"

#include <QLabel>
#include <QMouseEvent>
#include <QTimer>
#include <QVBoxLayout>

#include <quadrocore/quadro.h>


/**
 * @class PluginWidget
 */
/**
 * @fn PluginWidget
 */
PluginWidget::PluginWidget(PluginInterface *_interface, const QSize _size,
                           QWidget *_parent)
    : QWidget(_parent)
    , m_interface(_interface)
    , m_size(_size)
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;

    setContentsMargins(0, 0, 0, 0);
    setFixedSize(m_size);
    setLayout(new QVBoxLayout(this));
    // text
    m_textLabel = new QLabel(this);
    m_textLabel->setWordWrap(true);
    layout()->addWidget(m_textLabel);

    setMouseTracking(true);

    initPluginActions();
}


/**
 * @fn ~PluginWidget
 */
PluginWidget::~PluginWidget()
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;

    m_timer->stop();

    delete m_textLabel;
    delete m_timer;
}


/**
 * @fn mousePressEvent
 */
void PluginWidget::mousePressEvent(QMouseEvent *_event)
{
    if (_event->button() == Qt::LeftButton) {
        emit(widgetPressed());
    }

    QWidget::mousePressEvent(_event);
}


/**
 * @fn actionRequired
 */
void PluginWidget::actionRequired()
{
    return m_interface->action();
}


/**
 * @fn updateRequired
 */
void PluginWidget::updateRequired()
{
    m_interface->update();
    m_textLabel->setText(m_interface->data());

    // update background if any
    QString background = m_interface->background();
    if (!background.isEmpty())
        m_textLabel->setStyleSheet(
            QString("QLabel { background: %1; }").arg(background));
}


/**
 * @fn initPluginActions
 */
void PluginWidget::initPluginActions()
{
    m_timer = new QTimer(this);
    m_timer->setInterval(m_interface->updateInterval() >= MINIMAL_TIMER
                             ? m_interface->updateInterval()
                             : MINIMAL_TIMER);
    m_timer->setSingleShot(false);
    if (m_interface->updateInterval() != 0)
        m_timer->start();

    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateRequired()));
    connect(this, SIGNAL(widgetPressed()), this, SLOT(actionRequired()));
}
