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
 * @file pluginitem.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef PLUGINITEM_H
#define PLUGINITEM_H

#include <QtPlugin>

#include "config.h"


/**
 * @brief The PluginItem class provides plugin core part
 */
class PluginItem
{
public:
    /**
     * @brief PluginItem class destructor
     */
    virtual ~PluginItem();
    // get methods
    /**
     * @brief plugin API version
     * @return API version
     */
    virtual int api() const = 0;
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
    /**
     * @brief plugin name
     * @return name
     */
    virtual QString name() const = 0;
    // main methods
    /**
     * @brief method which will be called when plugin is activated
     */
    virtual void action() const = 0;
    /**
     * @brief init the plugin
     */
    virtual void init() = 0;
    /**
     * @brief quit from plugin
     */
    virtual void quit() = 0;
    /**
     * @brief read plugin settings from configuration file
     * @param _desktopPath   full path to settings file
     */
    virtual void readSettings(const QString _desktopPath) = 0;
    /**
     * @brief save plugin settings to configuration file
     * @param _desktopPath   full path to settings file
     * @return true if settings has been saved successfully
     * @return false if there was an error while settings sync
     */
    virtual bool saveSettings(const QString _desktopPath) = 0;
    /**
     * @brief update data
     */
    virtual void update() = 0;
};

Q_DECLARE_INTERFACE(PluginItem, PLUGIN_INTERFACE)


#endif /* PLUGINITEM_H */
