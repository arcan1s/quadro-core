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
 * @file applicationlaunheritem.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef APPLICATIONLAUNCHERITEM_H
#define APPLICATIONLAUNCHERITEM_H

#include <QMap>
#include <QProcess>
#include <QWidget>


/**
 * @brief The ApplicationLauncherItem class provides methods to control internal
 * applicaitons
 */
class ApplicationLauncherItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString command READ command)
    Q_PROPERTY(Q_PID pid READ processId)
    Q_PROPERTY(QProcess::ProcessState state READ processState)

public:
    /**
     * @brief ApplicationLauncherItem class constructor
     * @param parent         pointer to parent item (widget in which it will be
     *                       runned)
     * @param cmd            path to command which should be runned
     * @param debugCmd       show debug messages
     */
    explicit ApplicationLauncherItem(QWidget *parent, const QString cmd,
                                     const bool debugCmd = false);
    /**
     * @brief ApplicationLauncherItem class destructor
     */
    virtual ~ApplicationLauncherItem();
    // get methods
    /**
     * @brief command which is under control
     * @return path to command
     */
    QString command() const;
    /**
     * @brief PID of the child process
     * @return QProcess::processId()
     */
    Q_PID processId() const;
    /**
     * @brief status of the child process
     * @return state of the child process
     */
    QProcess::ProcessState processState() const;
    /**
     * @brief widget with run applicaiton
     * @return pointer to widget
     */
    QWidget *widget();

public slots:
    /**
     * @brief method to start the application
     */
    void startApplication();
    /**
     * @brief stop the application
     */
    void stopApplication();

private slots:
    /**
     * @brief called when process has been finished
     * @param exitCode       exit code of the application
     * @param exitStatus     exit status of the applicaiton
     */
    void finished(const int exitCode, const QProcess::ExitStatus exitStatus);

private:
    /**
     * @brief show debug messages. Default is false
     */
    bool debug = false;
    /**
     * @brief command line
     */
    QString m_command;
    /**
     * @brief pointer to the parent widget
     */
    QWidget *m_parent = nullptr;
    /**
     * @brief process item
     */
    QProcess *m_process = nullptr;
    /**
     * @brief widget which contains app
     */
    QWidget *m_widget = nullptr;
};


#endif /* APPLICATIONLAUNCHERITEM_H */
