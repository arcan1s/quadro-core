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
 * @file desktopplugin.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include <QDebug>
#include <QProcess>
#include <QSettings>

#include <quadro/quadro.h>
#include <pdebug/pdebug.h>
#include <task/taskadds.h>

#include "version.h"


/**
 * @class DesktopPlugin
 */
/**
 * @fn DesktopPlugin
 */
DesktopPlugin::DesktopPlugin(QObject *parent, const bool debugCmd)
    : PluginItem(parent, debugCmd),
      debug(debugCmd)
{
}


/**
 * @fn ~DesktopPlugin
 */
DesktopPlugin::~DesktopPlugin()
{
    if (debug) qDebug() << PDEBUG;
}


/**
 * @fn action
 */
QString DesktopPlugin::action()
{
    if (debug) qDebug() << PDEBUG;

    return m_action;
}


/**
 * @fn cmd
 */
QString DesktopPlugin::cmd()
{
    if (debug) qDebug() << PDEBUG;

    return m_cmd;
}


/**
 * @fn setAction
 */
void DesktopPlugin::setAction(const QString _actionCmd)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Action" << _actionCmd;

    m_action = _actionCmd;
}


/**
 * @fn setCmd
 */
void DesktopPlugin::setCmd(const QString _cmd)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Command" << _cmd;

    m_cmd = _cmd;
}


/**
 * @fn actionRequired
 */
void DesktopPlugin::actionRequired()
{
    if (debug) qDebug() << PDEBUG;
    if (action().isEmpty()) return;

    if (debug) qDebug() << PDEBUG << ":" << "Calling" << action();
    QProcess::startDetached(action());
}


/**
 * @fn readDesktop
 */
void DesktopPlugin::readDesktop(const QString _desktopPath)
{
    if (debug) qDebug() << PDEBUG;

    // basic settings
    PluginItem::readDesktop(_desktopPath);

    // custom settings
    QSettings settings(_desktopPath, QSettings::IniFormat);

    settings.beginGroup(QString("[Desktop plugin]"));
    setAction(settings.value(QString("Action"), m_action).toString());
    setCmd(settings.value(QString("Cmd"), m_cmd).toString());
    settings.endGroup();
}


QString DesktopPlugin::getBackground()
{
    if (debug) qDebug() << PDEBUG;

    return background();
}


QString DesktopPlugin::getData()
{
    if (debug) qDebug() << PDEBUG;

    if (debug) qDebug() << PDEBUG << ":" << "Run cmd" << cmd();
    TaskResult process = runTask(cmd());
    if (debug) qDebug() << PDEBUG << ":" << "Cmd returns" << process.exitCode;
    if (process.exitCode != 0)
        if (debug) qDebug() << PDEBUG << ":" << "Error" << process.error;

    return process.output;
}
