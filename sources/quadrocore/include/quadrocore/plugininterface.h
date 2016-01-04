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
 * @file plugininterface.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QtPlugin>

#include "config.h"
#include "quadroplugininterface.h"


/**
 * @brief The PluginInterface class provides plugin core part
 */
class PluginInterface : public QuadroPluginInterface
{
public:
    /**
     * @brief PluginInterface class destructor
     */
    virtual ~PluginInterface() {};
    /**
     * @brief method which generates new instance of PluginInterface class
     */
    virtual PluginInterface *createInstance() = 0;
    // get methods
    /**
     * @brief plugin background
     * @return background
     */
    virtual QString background() const = 0;
    /**
     * @brief plugin data in text
     * @return data
     */
    virtual QString data() const = 0;
    // main methods
    /**
     * @brief method which will be called when plugin is activated
     */
    virtual void action() const = 0;
    /**
     * @brief update data
     */
    virtual void update() = 0;
    /**
     * @brief current update interval in milliseconds
     */
    virtual int updateInterval() const = 0;
    /**
     * @brief widget size
     * @return widget size in application grids
     */
    virtual QSize widgetSize() const = 0;
};

Q_DECLARE_INTERFACE(PluginInterface, PLUGIN_INTERFACE)


#endif /* PLUGININTERFACE_H */
