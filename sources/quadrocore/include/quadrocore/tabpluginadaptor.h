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
 * @file tabpluginadaptor.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef TABPLUGINADAPTOR_H
#define TABPLUGINADAPTOR_H

#include "quadropluginadaptor.h"


class TabPluginInterface;

/**
 * @brief The PluginAdaptor class provides plugin DBus adaptor
 */
class TabPluginAdaptor : public QuadroPluginAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", DBUS_PLUGIN_INTERFACE)

public:
    /**
     * @brief PluginAdaptor class constructor
     * @param parent         pointer to parent object
     * @param plugin         pointer to plugin item
     */
    explicit TabPluginAdaptor(QObject *parent, TabPluginInterface *plugin);
    /**
     * @brief PluginAdaptor class destructor
     */
    virtual ~TabPluginAdaptor();

public slots:
    // public method interface
    /**
     * @brief update data. May be called to force update
     */
    Q_NOREPLY void Update();

private:
    // properties
    /**
     * @brief pointer to the plugin
     */
    TabPluginInterface *m_plugin = nullptr;
};


#endif /* TABPLUGINADAPTOR_H */
