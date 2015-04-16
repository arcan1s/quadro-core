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
 * @file desktopplugin.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef DESKTOPPLUGIN_H
#define DESKTOPPLUGIN_H

#include <QImage>
#include <QMap>
#include <QObject>
#include <QVariant>

#include "pluginitem.h"


/**
 * @brief The DesktopPlugin class provides desktop plugin core part
 */
class DesktopPlugin : public PluginItem
{
    Q_OBJECT
    // core properties
    Q_PROPERTY(QString action READ action WRITE setAction)
    Q_PROPERTY(QString cmd READ cmd WRITE setCmd)

public:
    /**
     * @brief DesktopPlugin class constructor
     * @param parent         pointer to parent item
     * @param debugCmd       show debug messages
     */
    explicit DesktopPlugin(QObject *parent, const bool debugCmd = false);
    /**
     * @brief DesktopPlugin class destructor
     */
    ~DesktopPlugin();
    // get methods
    /**
     * @brief plugin action command
     * @return action command
     */
    QString action();
    /**
     * @brief plugin command line
     * @return command
     */
    QString cmd();
    // set methods
    /**
     * @brief set plugin action command line
     * @param _actionCmd     action command line
     */
    void setAction(const QString _actionCmd);
    /**
     * @brief set plugin command line
     * @param _cmd           command line
     */
    void setCmd(const QString _cmd);

public slots:
    /**
     * @brief called if plugin has been clicked
     */
    void actionRequired();
    /**
     * @brief read plugin information from desktop file
     * @param _desktopPath   full path to desktop file
     */
    void readDesktop(const QString _desktopPath);

private:
    /**
     * @brief show debug messages. Default is false
     */
    bool debug = false;
    // properties
    /**
     * @brief plugin action command line. Default is empty
     */
    QString m_action = QString();
    /**
     * @brief plugin command line. Default is empty
     */
    QString m_cmd = QString();
    // methods
    /**
     * @brief update image from source
     * @return new background
     */
    QString getBackground();
    /**
     * @brief update data from source. Should be implemented by any derivative
     * class
     * @return new data
     */
    QString getData();
};


#endif /* DESKTOPPLUGIN_H */
