/***************************************************************************
 *   This file is part of netctl-gui                                       *
 *                                                                         *
 *   netctl-gui is free software: you can redistribute it and/or           *
 *   modify it under the terms of the GNU General Public License as        *
 *   published by the Free Software Foundation, either version 3 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   netctl-gui is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with netctl-gui. If not, see http://www.gnu.org/licenses/       *
 ***************************************************************************/


#include <QApplication>
#include <QDir>

#include "messages.h"
#include "version.h"


QString errorMessage()
{
    return QApplication::translate("MainWindow", "Unknown flag\n");
}


QVariantMap getArgs()
{
    QVariantMap args;
    // windows
    args[QString("nodaemon")] = false;
    args[QString("minimized")] = false;
    // main functions
    args[QString("essid")] = QString("ESSID");
    args[QString("open")] = QString("PROFILE");
    args[QString("select")] = QString("PROFILE");
    // additional functions
    args[QString("config")] = QString("%1/.config/quadro.conf").arg(QDir::homePath());
    args[QString("debug")] = true;
    args[QString("defaults")] = false;
    // messages
    args[QString("error")] = false;
    args[QString("help")] = false;
    args[QString("info")] = false;
    args[QString("version")] = false;

    return args;
}


QString helpMessage()
{
    QString helpMessage = QString("");
    helpMessage += QString("%1\n").arg(QApplication::translate("MainWindow", "Usage:"));
    helpMessage += QString("quadro [ options ]\n");
    helpMessage += QString("%1\n").arg(QApplication::translate("MainWindow", "Options:"));
    // windows
    helpMessage += QString(" %1\n").arg(QApplication::translate("MainWindow", "Open window:"));
    helpMessage += QString("       --nodaemon        - %1\n").arg(QApplication::translate("MainWindow", "do not detach from console"));
    helpMessage += QString("       --minimized       - %1\n").arg(QApplication::translate("MainWindow", "start minimized to tray"));
    // additional functions
    helpMessage += QString(" %1\n").arg(QApplication::translate("MainWindow", "Additional flags:"));
    helpMessage += QString("   -c, --config <arg>    - %1\n").arg(QApplication::translate("MainWindow", "read configuration from this file"));
    helpMessage += QString("   -d, --debug           - %1\n").arg(QApplication::translate("MainWindow", "print debug information"));
    helpMessage += QString("       --default         - %1\n").arg(QApplication::translate("MainWindow", "start with default settings"));
    // messages
    helpMessage += QString(" %1\n").arg(QApplication::translate("MainWindow", "Show messages:"));
    helpMessage += QString("   -v, --version         - %1\n").arg(QApplication::translate("MainWindow", "show version and exit"));
    helpMessage += QString("   -i, --info            - %1\n").arg(QApplication::translate("MainWindow", "show build information and exit"));
    helpMessage += QString("   -h, --help            - %1\n").arg(QApplication::translate("MainWindow", "show this help and exit"));

    return helpMessage;
}


QString infoMessage()
{
    QString infoMessage = QString("");
    // build information
    infoMessage += QApplication::translate("MainWindow", "Build date: %1").arg(QString(BUILD_DATE));
    // cmake
    infoMessage += QString("\n%1:\n").arg(QApplication::translate("MainWindow", "cmake flags"));
    // cmake properties
    infoMessage += QString("%1:\n").arg(QApplication::translate("MainWindow", "cmake properties"));
    infoMessage += QString("\t-DCMAKE_BUILD_TYPE=%1\n").arg(QString(CMAKE_BUILD_TYPE));
    infoMessage += QString("\t-DCMAKE_INSTALL_PREFIX=%1\n").arg(QString(CMAKE_INSTALL_PREFIX));
    // components
    // additional components
    infoMessage += QString("%1:\n").arg(QApplication::translate("MainWindow", "Additional components"));
    infoMessage += QString("\t-DBUILD_DOCS=%1\n").arg(QString(PROJECT_BUILD_DOCS));
    infoMessage += QString("\t-DBUILD_TEST=%1\n").arg(QString(PROJECT_BUILD_TEST));
    // project properties
    infoMessage += QString("%1:\n").arg(QApplication::translate("MainWindow", "Project properties"));
    infoMessage += QString("\tDOCS_PATH=%1\n").arg(QString(DOCS_PATH));
    infoMessage += QString("\tFAVORITES_PATH=%1\n").arg(QString(FAVORITES_PATH));
    infoMessage += QString("\tHOME_PATH=%1\n").arg(QString(HOME_PATH));
    infoMessage += QString("\tPLUGIN_PATH=%1\n").arg(QString(PLUGIN_PATH));
    // plugin properties
    infoMessage += QString("%1:\n").arg(QApplication::translate("MainWindow", "Plugin properties"));
    infoMessage += QString("\tMINIMAL_TIMER=%1\n").arg(QString(MINIMAL_TIMER));
    infoMessage += QString("\tPLUGIN_API=%1\n").arg(QString(PLUGIN_API));
    // transport information
    infoMessage += QString("%1:\n").arg(QApplication::translate("MainWindow", "DBus configuration"));
    infoMessage += QString("\tDBUS_SERVICE=%1\n").arg(QString(DBUS_SERVICE));
    infoMessage += QString("\tDBUS_PLUGIN_SERVICE=%1\n").arg(QString(DBUS_PLUGIN_SERVICE));
    infoMessage += QString("\tDBUS_INTERFACE=%1\n").arg(QString(DBUS_INTERFACE));
    infoMessage += QString("\tDBUS_PLUGIN_INTERFACE=%1\n").arg(QString(DBUS_PLUGIN_INTERFACE));
    infoMessage += QString("\tDBUS_OBJECT_PATH=%1\n").arg(QString(DBUS_OBJECT_PATH));

    return infoMessage;
}


QString versionMessage()
{
    QString versionMessage = QString("");
    versionMessage += QString("%1\n").arg(QString(NAME));
    versionMessage += QString("%1 : %2\n").arg(QApplication::translate("MainWindow", "Version")).arg(QString(VERSION));
    versionMessage += QString("%1 : %2\n").arg(QApplication::translate("MainWindow", "Author")).arg(QString(AUTHOR));
    versionMessage += QString("%1 : %2\n").arg(QApplication::translate("MainWindow", "License")).arg(QString(LICENSE));

    return versionMessage;
}
