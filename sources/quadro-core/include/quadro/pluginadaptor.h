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
 * @file pluginadaptor.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef PLUGINADAPTOR_H
#define PLUGINADAPTOR_H

#include <QDBusAbstractAdaptor>
#include <QObject>

#include "version.h"


class PluginItem;

/**
 * @brief The PluginAdaptor class provides plugin DBus adaptor
 */
class PluginAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", DBUS_PLUGIN_INTERFACE)

public:
    /**
     * @brief PluginAdaptor class constructor
     * @param plugin         pointer to plugin item
     * @param debugCmd       show debug messages
     */
    explicit PluginAdaptor(PluginItem *plugin,
                           const bool debugCmd = false);
    /**
     * @brief PluginAdaptor class destructor
     */
    ~PluginAdaptor();
    /**
     * @brief plugin name
     * @return name
     */
    QString name();

public slots:

private:
    /**
     * @brief show debug messages. Default is false
     */
    bool debug = false;
    // properties
    /**
     * @brief pointer to the plugin
     */
    PluginItem *m_plugin = nullptr;
};


#endif /* PLUGINADAPTOR_H */
