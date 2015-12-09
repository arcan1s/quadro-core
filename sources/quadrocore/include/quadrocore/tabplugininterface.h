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
 * @file tabplugininterface.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef TABPLUGININTERFACE_H
#define TABPLUGININTERFACE_H

#include "quadroplugininterface.h"


/**
 * @brief The TabPluginInterface class provides core part of plugin run in own tab
 */
class TabPluginInterface : public QuadroPluginInterface
{
public:
    /**
     * @brief TabPluginInterface class destructor
     */
    virtual ~TabPluginInterface() {};
    // get methods
    /**
     * @brief plugin ui object
     * @return pointer to QWidget object
     */
    virtual QWidget *widget() = 0;
};

Q_DECLARE_INTERFACE(TabPluginInterface, TAB_PLUGIN_INTERFACE)


#endif /* TABPLUGININTERFACE_H */
