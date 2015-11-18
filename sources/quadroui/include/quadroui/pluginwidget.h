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
 * @file pluginwidget.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef PLUGINWIDGET_H
#define PLUGINWIDGET_H

#include <QSize>
#include <QWidget>
#include <quadrocore/plugincore.h>
#include <quadrocore/plugininterface.h>


class PluginInterface;
class QLabel;

/**
 * @brief The PluginWidget class provides generic UI representation
 */
class PluginWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief PluginWidget class constructor
     * @param interface      pointer to plugin interface
     * @param size           item size
     * @param parent         pointer to parent object
     */
    explicit PluginWidget(PluginInterface *interface, const QSize size, QWidget *parent);
    /**
     * @brief PluginWidget class destructor
     */
    virtual ~PluginWidget();

signals:
    /**
     * @brief signal which will be emitted when widget will be pressed
     */
    void widgetPressed();

protected:
    /**
     * @brief method which will be called on mouse event
     * @param _event         pointer to mouse event
     */
    void mousePressEvent(QMouseEvent *_event);

private slots:
    /**
     * @brief method which will be called to return interface action
     */
    void actionRequired();
    /**
    * @brief method which will be called to update widget
    */
    void updateRequired();

private:
    // methods
    /**
     * @brief method to init plugin actions, timers, etc
     */
    void initPluginActions();
    // ui
    /**
     * @brief pointer to QLabel with text
     */
    QLabel *m_textLabel = nullptr;
    // properties
    /**
     * @brief pointer to plugin interface
     */
    PluginInterface *m_interface = nullptr;
    /**
     * @brief UI size
     */
    QSize m_size;
    /**
     * @brief timer for interface updates
     */
    QTimer *m_timer = nullptr;
};


#endif /* PLUGINWIDGET_H */
