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
 * @class StandaloneApplicationItem
 */
/**
 * @fn StandaloneApplicationItem
 */
StandaloneApplicationItem::StandaloneApplicationItem(QWidget *parent, const QStringList cmd)
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
 * @fn ~StandaloneApplicationItem
 */
StandaloneApplicationItem::~StandaloneApplicationItem()
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;

    m_widgets.clear();
    m_process->kill();
    m_process->deleteLater();
}


/**
 * @fn command
 */
QStringList StandaloneApplicationItem::command() const
{
    return m_command;
}


/**
 * @fn processId
 */
Q_PID StandaloneApplicationItem::processId() const
{
    if (m_process == nullptr) return 0;

    return m_process->processId();
}


/**
 * @fn processState
 */
QProcess::ProcessState StandaloneApplicationItem::processState() const
{
    if (m_process == nullptr) return QProcess::NotRunning;

    return m_process->state();
}


/**
 * @fn widget
 */
QList<QWidget *> StandaloneApplicationItem::widgets()
{
    return m_widgets;
}


/**
 * @fn startApplication
 */
void StandaloneApplicationItem::startApplication()
{
    if (m_process == nullptr) return;

    QStringList cmdArgs = m_command;
    QString cmd = cmdArgs.takeFirst();

    m_process->start(cmd, cmdArgs);
}


/**
 * @fn stopApplication
 */
void StandaloneApplicationItem::stopApplication()
{
    if (m_process == nullptr) return;

    m_process->terminate();
}


/**
 * @fn updateWidgets
 */
void StandaloneApplicationItem::updateWidgets()
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
void StandaloneApplicationItem::finished(const int exitCode,
                                       const QProcess::ExitStatus exitStatus)
{
    qCDebug(LOG_LIB) << "Exit code" << exitCode;
    qCDebug(LOG_LIB) << "Exit status" << exitStatus;

    m_widgets.clear();
}
