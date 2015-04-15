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
 * @file pluginadaptor.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef PLUGINADAPTOR_H
#define PLUGINADAPTOR_H

#include <QDBusAbstractAdaptor>
#include <QObject>

#include "version.h"


class PluginItem;

/**
 * @brief The PluginAdaptor class provides plugin DBus adaptor
 */
class PluginAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", DBUS_PLUGIN_INTERFACE)

public:
    /**
     * @brief PluginAdaptor class constructor
     * @param plugin         pointer to plugin item
     * @param debugCmd       show debug messages
     */
    explicit PluginAdaptor(PluginItem *plugin,
                           const bool debugCmd = false);
    /**
     * @brief PluginAdaptor class destructor
     */
    ~PluginAdaptor();

public slots:
    /**
     * @brief ping interface
     * @return true if interface is active
     */
    bool Ping();
    // public method interface
    /**
     * @brief plugin API version
     * @return API version
     */
    int Api();
    /**
     * @brief plugin background
     * @return background
     */
    QString Background();
    /**
     * @brief plugin comment
     * @return comment
     */
    QString Comment();
    /**
     * @brief plugin current settings which will be applied on next start
     * @return configuration list in format KEY=VALUE
     */
    QStringList Configuration();
    /**
     * @brief plugin data in text
     * @return data
     */
    QString Data();
    /**
     * @brief has plugin UI or not
     * @return true if it has one
     * @return false it it hasn't UI
     */
    bool HasUi();
    /**
     * @brief plugin UI height
     * @return height in UI grids
     */
    int Height();
    /**
     * @brief plugin UI image. It fills from background()
     * @return QImage object
     */
    QString HtmlImage();
    /**
     * @brief plugin name
     * @return name
     */
    QString Name();
    /**
     * @brief plugin events timer
     * @return plugin timer in milliseconds. May be more than MINIMAL_TIMER or
     * less than 0 in case of skiping automatic update
     */
    int Timer();
    /**
     * @brief plugin UI width
     * @return width in UI grids
     */
    int Width();
    // public slots interface
    /**
     * @brief called if plugin has been clicked
     */
    void Action();
    /**
     * @brief close the plugin
     */
    void Close();
    /**
     * @brief read plugin information from desktop file
     * @param desktopPath    full path to desktop file
     */
    void ReadDesktop(const QString desktopPath);
    /**
     * @brief read plugin settings from configuration file
     * @param desktopPath    full path to settings file
     */
    void ReadSettings(const QString desktopPath);
    /**
     * @brief save plugin settings to configuration file
     * @param desktopPath    full path to settings file
     * @return true if settings has been saved successfully
     * @return false if there was an error while settings sync
     */
    bool SaveSettings(const QString desktopPath);
    /**
     * @brief update data. May be called to force update
     */
    void Update();
    /**
     * @brief method which will be called on data update
     * @param data           updated data
     * @remark dirty hack to allow signal call from external class since in Qt4
     * signals are private
     */
    void UpdatesReceived(const QString data);

signals:
    /**
     * @brief send if data has been updated
     * @param data           updated data
     */
    void Updated(QString data);

private:
    /**
     * @brief show debug messages. Default is false
     */
    bool debug = false;
    // properties
    /**
     * @brief pointer to the plugin
     */
    PluginItem *m_plugin = nullptr;
};


#endif /* PLUGINADAPTOR_H */
