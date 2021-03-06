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
 * @file PluginAdaptor.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef PLUGINADAPTOR_H
#define PLUGINADAPTOR_H

#include <QDBusVariant>

#include "QuadroPluginadaptor.h"


/**
 * @namespace Quadro
 */
namespace Quadro
{
class PluginInterface;

/**
 * @brief The PluginAdaptor class provides plugin DBus adaptor
 */
class PluginAdaptor : public QuadroPluginAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", DBUS_PLUGIN_INTERFACE_NAME)

public:
    /**
     * @brief PluginAdaptor class constructor
     * @param _parent pointer to parent object
     * @param _plugin pointer to plugin item
     */
    explicit PluginAdaptor(QObject *_parent, PluginInterface *_plugin);

    /**
     * @brief PluginAdaptor class destructor
     */
    virtual ~PluginAdaptor();

public slots:
    // public method interface
    /**
     * @brief plugin background
     * @return background
     */
    QString Background() const;

    /**
     * @brief plugin data in text
     * @return data
     */
    QString Data() const;
    /**
     * @brief called if plugin has been clicked
     */
    Q_NOREPLY void Action();

    /**
     * @brief get plugin size
     * @return list of size in format [width, height]
     */
    QDBusVariant Size() const;
    /**
     * @brief update data. May be called to force update
     */
    Q_NOREPLY void Update();

    /**
     * @brief plugin update interval
     * @return update interval in milliseconds
     */
    int UpdateInterval() const;

private:
    // properties
    /**
     * @brief pointer to the plugin
     */
    PluginInterface *m_plugin = nullptr;
};
};


#endif /* PLUGINADAPTOR_H */
