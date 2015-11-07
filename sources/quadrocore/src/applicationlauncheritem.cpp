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
 * @file applicationlauncheritem.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadrocore/quadro.h"

#include <QHash>
#include <QTimer>
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

    m_process = new QProcess(nullptr);
    connect(m_process, SIGNAL(started()), this, SLOT(updateWidgets()));
    connect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)),
            this, SLOT(finished(int, QProcess::ExitStatus)));
}


/**
 * @fn ~ApplicationLauncherItem
 */
ApplicationLauncherItem::~ApplicationLauncherItem()
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;

    m_widgets.clear();
    m_process->kill();
    m_process->deleteLater();
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
QList<QWidget *> ApplicationLauncherItem::widgets()
{
    return m_widgets;
}


/**
 * @fn startApplication
 */
void ApplicationLauncherItem::startApplication()
{
    if (m_process == nullptr) return;

    //run process and find its wid
    m_process->start(m_command);
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
 * @fn updateWidgets
 */
void ApplicationLauncherItem::updateWidgets()
{
    if (processId() == 0) {
        qCCritical(LOG_LIB) << "Cound not get PID";
        return;
    }

    QList<WId> windows = X11Adaptor::getWindowByPid(processId());
    if (windows.isEmpty()) {
        qCCritical(LOG_LIB) << "Could not find window for PID" << processId();
        return QTimer::singleShot(333, this, SLOT(updateWidgets()));
    }
    qCInfo(LOG_UI) << "Found WIds" << windows << "for PID" << processId();

    // init widget
    m_widgets.clear();
    foreach (WId id, windows)
        m_widgets.append(QWidget::createWindowContainer(QWindow::fromWinId(id), m_parent));

    return emit(ready());
}


/**
 * @fn finished
 */
void ApplicationLauncherItem::finished(const int exitCode,
                                       const QProcess::ExitStatus exitStatus)
{
    qCDebug(LOG_LIB) << "Exit code" << exitCode;
    qCDebug(LOG_LIB) << "Exit status" << exitStatus;

    m_widgets.clear();
}
