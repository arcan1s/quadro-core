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
 * @file QuadroDebug.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef QUADRODEBUG_H
#define QUADRODEBUG_H

#include <QLoggingCategory>


/**
 * @brief DBus logging category
 */
Q_DECLARE_LOGGING_CATEGORY(LOG_DBUS)
/**
 * @brief library logging category
 */
Q_DECLARE_LOGGING_CATEGORY(LOG_LIB)
/**
 * @brief plugin logging category
 */
Q_DECLARE_LOGGING_CATEGORY(LOG_PL)
/**
 * @brief UI logging category
 */
Q_DECLARE_LOGGING_CATEGORY(LOG_UI)
/**
 * @brief UI library logging category
 */
Q_DECLARE_LOGGING_CATEGORY(LOG_UILIB)


/**
 * @namespace Quadro
 */
namespace Quadro
{
namespace QuadroDebug
{
/**
 * @brief default log format
 */
const char LOG_FORMAT[] = "[%{time "
                          "process}][%{if-debug}DD%{endif}%{if-info}II%{endif}%"
                          "{if-warning}WW%{endif}%{if-critical}CC%{endif}%{if-"
                          "fatal}FF%{endif}][%{category}][%{function}] "
                          "%{message}";
/**
 * @brief method to apply log format
 */
void applyLogFormat();
/**
 * @brief method to enable debug messages
 */
void enableDebug();
/**
 * @brief additional method to get build details declared in version.h
*/
QStringList getBuildData();
};
};


#endif /* QUADRODEBUG_H */
