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
 * @file PluginContainer.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef PLUGINCONTAINER_H
#define PLUGINCONTAINER_H

#include <QSize>

#include "QuadroWidget.h"


/**
 * @namespace Quadro
 */
namespace Quadro
{
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
     * @param _parent pointer to parent object
     * @param _grid grid size
     * @param _widgetTitle widget title
     * @param _hPolicy horizontal scroll bar policy
     * @param _vPolicy vertical scroll bar policy
     */
    explicit PluginContainer(QWidget *_parent, const int _grid,
                             const QString _widgetTitle = "none",
                             const Qt::ScrollBarPolicy _hPolicy
                             = Qt::ScrollBarAlwaysOff,
                             const Qt::ScrollBarPolicy _vPolicy
                             = Qt::ScrollBarAsNeeded);

    /**
     * @brief PluginContainer class destructor
     */
    virtual ~PluginContainer();

    /**
     * @brief add plugin to the position
     * @param _interface pointer to plugin interface
     */
    void addPlugin(PluginInterface *_interface);
};
};


#endif /* PLUGINCONTAINER_H */
