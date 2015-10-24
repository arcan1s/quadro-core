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


#include "quadro/quadro.h"

#include <QWindow>


/**
 * @class ApplicationLauncherItem
 */
/**
 * @fn ApplicationLauncherItem
 */
ApplicationLauncherItem::ApplicationLauncherItem(QWidget *parent, const QString cmd)
    : QObject(parent),
      m_command(cmd),
      m_parent(parent)
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;

    m_process = new QProcess(this);
    connect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)),
            this, SLOT(finished(int, QProcess::ExitStatus)));
}


/**
 * @fn ~ApplicationLauncherItem
 */
ApplicationLauncherItem::~ApplicationLauncherItem()
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;

    delete m_process;
    delete m_widget;
}


/**
 * @fn command
 */
QString ApplicationLauncherItem::command() const
{
    return m_command;
}


/**
 * @fn processId
 */
Q_PID ApplicationLauncherItem::processId() const
{
    if (m_process == nullptr) return 0;

    return m_process->processId();
}


/**
 * @fn processState
 */
QProcess::ProcessState ApplicationLauncherItem::processState() const
{
    if (m_process == nullptr) return QProcess::NotRunning;

    return m_process->state();
}


/**
 * @fn widget
 */
QWidget *ApplicationLauncherItem::widget()
{
    return m_widget;
}


/**
 * @fn startApplication
 */
void ApplicationLauncherItem::startApplication()
{
    if (m_process == nullptr) return;

    //run process and find its wid
    m_process->start(m_command);
    QMap<Q_PID, WId> windows = X11Adaptor::getWindowsList();
    if (!windows.contains(processId())) {
        qCWarning(LOG_LIB) << "Could not find window for PID" << processId();
        return;
    }

    // init widget
    QWindow *window = QWindow::fromWinId(windows[processId()]);
    // delete widget if exist
    delete m_widget;
    m_widget = QWidget::createWindowContainer(window, m_parent, Qt::SubWindow);
}


/**
 * @fn stopApplication
 */
void ApplicationLauncherItem::stopApplication()
{
    if (m_process == nullptr) return;

    m_process->terminate();
}


/**
 * @fn finished
 */
void ApplicationLauncherItem::finished(const int exitCode,
                                       const QProcess::ExitStatus exitStatus)
{
    qCDebug(LOG_LIB) << "Exit code" << exitCode;
    qCDebug(LOG_LIB) << "Exit status" << exitStatus;

    delete m_widget;
    m_widget = nullptr;
}
