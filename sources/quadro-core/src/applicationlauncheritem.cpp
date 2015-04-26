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
 * @file applicationlaunheritem.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include <QDebug>
#include <QWindow>

#include <quadro/quadro.h>
#include <pdebug/pdebug.h>


/**
 * @class ApplicationLauncherItem
 */
/**
 * @fn ApplicationLauncherItem
 */
ApplicationLauncherItem::ApplicationLauncherItem(QWidget *parent, const QString cmd,
                                                 const bool debugCmd)
    : QObject(parent),
      debug(debugCmd),
      m_command(cmd),
      m_parent(parent)
{
    m_process = new QProcess(this);
    connect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)),
            this, SLOT(finished(int, QProcess::ExitStatus)));
}


/**
 * @fn ~ApplicationLauncherItem
 */
ApplicationLauncherItem::~ApplicationLauncherItem()
{
    if (debug) qDebug() << PDEBUG;

    if (m_process != nullptr) delete m_process;
    if (m_widget != nullptr) delete m_widget;
}


/**
 * @fn command
 */
QString ApplicationLauncherItem::command()
{
    if (debug) qDebug() << PDEBUG;

    return m_command;
}


/**
 * @fn processId
 */
Q_PID ApplicationLauncherItem::processId()
{
    if (debug) qDebug() << PDEBUG;
    if (m_process == nullptr) return 0;

    return m_process->processId();
}


/**
 * @fn processState
 */
QProcess::ProcessState ApplicationLauncherItem::processState()
{
    if (debug) qDebug() << PDEBUG;
    if (m_process == nullptr) return QProcess::NotRunning;

    return m_process->state();
}


/**
 * @fn widget
 */
QWidget *ApplicationLauncherItem::widget()
{
    if (debug) qDebug() << PDEBUG;

    return m_widget;
}


/**
 * @fn startApplication
 */
void ApplicationLauncherItem::startApplication()
{
    if (debug) qDebug() << PDEBUG;
    if (m_process == nullptr) return;

    //run process and find its wid
    m_process->start(m_command);
    QMap<Q_PID, WId> windows = X11Adaptor::getWindowsList(debug);
    if (!windows.contains(processId())) {
        if (debug) qDebug() << PDEBUG << ":" << "Could not find window for PID" << processId();
        return;
    }

    // init widget
    QWindow *window = QWindow::fromWinId(windows[processId()]);
    // delete widget if exist
    if (m_widget != nullptr) delete m_widget;
    m_widget = QWidget::createWindowContainer(window, m_parent, Qt::SubWindow);
}


/**
 * @fn stopApplication
 */
void ApplicationLauncherItem::stopApplication()
{
    if (debug) qDebug() << PDEBUG;
    if (m_process == nullptr) return;

    m_process->terminate();
}


/**
 * @fn finished
 */
void ApplicationLauncherItem::finished(const int exitCode,
                                       const QProcess::ExitStatus exitStatus)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Exit code" << exitCode;
    if (debug) qDebug() << PDEBUG << ":" << "Exit status" << exitStatus;

    if (m_widget != nullptr) delete m_widget;
}
