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
 * @file QuadroPluginadaptor.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef QUADROPLUGINADAPTOR_H
#define QUADROPLUGINADAPTOR_H

#include <QDBusAbstractAdaptor>
#include <QObject>

#include "Config.h"


/**
 * @namespace Quadro
 */
namespace Quadro
{
class QuadroPluginInterface;

/**
 * @brief The QuadroPluginAdaptor class provides plugin DBus adaptor
 */
class QuadroPluginAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", DBUS_PLUGIN_INTERFACE_NAME)

public:
    /**
     * @brief QuadroPluginAdaptor class constructor
     * @param _parent pointer to parent object
     * @param _plugin pointer to plugin item
     */
    explicit QuadroPluginAdaptor(QObject *_parent,
                                 QuadroPluginInterface *_plugin);
    /**
     * @brief QuadroPluginAdaptor class destructor
     */
    virtual ~QuadroPluginAdaptor();

public slots:
    /**
     * @brief ping interface
     * @return true if interface is active
     */
    bool Ping() const;
    // public method interface
    /**
     * @brief plugin name
     * @return name
     */
    QString Name() const;
    /**
     * @brief init plugin
     */
    Q_NOREPLY void Init();
    /**
     * @brief close the plugin
     * @param configPath full path to settings file
     */
    Q_NOREPLY void Quit(const QString &configPath);
    /**
     * @brief read plugin settings from configuration file
     * @param configPath full path to settings file
     */
    void ReadSettings(const QString &configPath);
    /**
     * @brief save settings from configuration UI
     */
    void SaveSettings();
    /**
     * @brief save plugin settings to configuration file
     * @param configPath full path to settings file
     * @return true if settings has been saved successfully
     * @return false if there was an error while settings sync
     */
    bool WriteSettings(const QString &configPath) const;

private:
    // properties
    /**
     * @brief pointer to the plugin
     */
    QuadroPluginInterface *m_plugin = nullptr;
};
};


#endif /* QuadroPLUGINADAPTOR_H */
