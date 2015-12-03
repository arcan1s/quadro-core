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
 * @file quadroplugininterface.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef QUADROPLUGININTERFACE_H
#define QUADROPLUGININTERFACE_H

#include <QWidget>


class QuadroCore;

/**
 * @brief The QuadroPluginInterface class provides generic plugin interfaces
 */
class QuadroPluginInterface
{
public:
    /**
     * @brief QuadroPluginInterface class destructor
     */
    virtual ~QuadroPluginInterface() {};
    // get methods
    /**
     * @brief pointer to configuration widget. If returning pointer will not be
     * nullptr the additional configuration page will be created
     * @return pointer to configuration widget
     */
    virtual QWidget *configWidget() = 0;
    /**
     * @brief plugin name
     * @return name
     */
    virtual QString name() const = 0;
    // main methods
    /**
     * @brief init the plugin
     */
    virtual void init() = 0;
    /**
     * @brief quit from plugin
     * @param _configPath    full path to settings file
     */
    virtual void quit(const QString _configPath) = 0;
    /**
     * @brief read plugin settings from configuration file
     * @param _configPath    full path to settings file
     */
    virtual void readSettings(const QString _configPath) = 0;
    /**
     * @brief save plugin settings to configuration file
     * @param _configPath    full path to settings file
     * @return true if settings has been saved successfully
     * @return false if there was an error while settings sync
     */
    virtual bool saveSettings(const QString _configPath) = 0;
    /**
     * @brief additional method which will be called to pass required args
     * @remark this method will be called before QuadroPluginInterface::init()
     * @param _core          pointer to core object
     * @param _settings      application settings
     */
    virtual void setArgs(QuadroCore *_core, const QVariantHash _settings) = 0;
};


#endif /* QUADROPLUGININTERFACE_H */
