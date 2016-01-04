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
 * @file plugincontainer.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef PLUGINCONTAINER_H
#define PLUGINCONTAINER_H

#include <QSize>

#include "quadrowidget.h"


class PluginInterface;

/**
 * @brief The PluginContainer class provides generic UI container for plugins
 */
class PluginContainer : public QuadroWidget
{
    Q_OBJECT

public:
    /**
     * @brief PluginContainer class constructor
     * @param parent         pointer to parent object
     * @param grid           grid size
     * @param widgetTitle    widget title
     * @param hPolicy        horizontal scroll bar policy
     * @param vPolicy        vertical scroll bar policy
     */
    explicit PluginContainer(QWidget *parent, const int grid,
                             const QString widgetTitle = QString("none"),
                             const Qt::ScrollBarPolicy hPolicy = Qt::ScrollBarAlwaysOff,
                             const Qt::ScrollBarPolicy vPolicy = Qt::ScrollBarAsNeeded);
    /**
     * @brief PluginContainer class destructor
     */
    virtual ~PluginContainer();
    /**
     * @brief add plugin to the position
     * @param _interface     pointer to plugin interface
     */
    void addPlugin(PluginInterface *_interface);
};


#endif /* PLUGINCONTAINER_H */
