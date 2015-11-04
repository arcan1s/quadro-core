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
 * @file config.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef CONFIG_H
#define CONFIG_H

// dbus configuration
/**
 * @def DBUS_SERVICE
 * DBus service name for library and ui
 */
#define DBUS_SERVICE "org.quadro.core"
/**
 * @def DBUS_PLUGIN_SERVICE
 * DBus service name for plugins
 */
#define DBUS_PLUGIN_SERVICE "org.quadro.plugin"
/**
 * @def DBUS_INTERFACE
 * DBus interface name for library and ui
 */
#define DBUS_INTERFACE "org.quadro.core"
/**
 * @def DBUS_PLUGIN_INTERFACE
 * DBus service name for plugins
 */
#define DBUS_PLUGIN_INTERFACE "org.quadro.plugin"
/**
 * @def DBUS_OBJECT_PATH
 * DBus object path for library
 */
#define DBUS_OBJECT_PATH "/quadro"
/**
 * @def DBUS_UI_OBJECT_PATH
 * DBus object path for ui
 */
#define DBUS_UI_OBJECT_PATH "/ui"

// path configuration
/**
 * @def FAVORITES_PATH
 * path to favorites inside @ref HOME_PATH
 */
#define FAVORITES_PATH "favorites"
/**
 * @def HOME_PATH
 * path to quadro home directory
 */
#define HOME_PATH "quadro"
/**
 * @def PLUGIN_PATH
 * path to plugins inside @ref HOME_PATH
 */
#define PLUGIN_PATH "plugins"
/**
 * @def RECENT_PATH
 * path to recent items inside @ref HOME_PATH
 */
#define RECENT_PATH "recent"

// plugin configuration
/**
 * @def MINIMAL_TIMER
 * minimal available time for plugin update
 */
#define MINIMAL_TIMER 333
/**
 * @def PLUGIN_API
 * current plugin API
 */
#define PLUGIN_API 1
/**
 * @def TAB_PLUGIN_API
 * current tab plugin API
 */
#define TAB_PLUGIN_API 1

#endif /* CONFIG_H */
