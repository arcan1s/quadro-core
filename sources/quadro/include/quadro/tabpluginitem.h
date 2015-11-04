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
 * @file tabpluginitem.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef TABPLUGINITEM_H
#define TABPLUGINITEM_H

#include <QMainWindow>
#include <QtPlugin>
#include "quadrocore.h"


class QuadroCore;

/**
 * @brief The TabPluginItem class provides core part of plugin run in different tab
 */
class TabPluginItem : public QMainWindow
{
    Q_OBJECT
//    // core properties
//    Q_PROPERTY(int api READ api WRITE setApi)
//    Q_PROPERTY(QString comment READ comment WRITE setComment)
//    Q_PROPERTY(QuadroCore * core READ core)
//    Q_PROPERTY(QString name READ name WRITE setName)

public:
    /**
     * @brief TabPluginItem class constructor
     * @param parent         pointer to parent item
     */
//    explicit TabPluginItem(QWidget *parent);
    /**
     * @brief TabPluginItem class destructor
     */
    virtual ~TabPluginItem();
    /**
     * @brief read plugin information from desktop file
     * @param _desktopPath   full path to desktop file
     */
    static QVariantHash readDesktop(const QString _desktopPath);
    // get methods
    /**
     * @brief plugin API version
     * @return API version
     */
    int api() const;
    /**
     * @brief plugin comment
     * @return comment
     */
    QString comment() const;
    /**
     * @brief core object
     * @return pointer to core object
     */
    QuadroCore *core();
    /**
     * @brief plugin name
     * @return name
     */
    QString name() const;
    // set methods
    /**
     * @brief set API version
     * @param _api           plugin API version
     */
    void setApi(int _api = 1);
    /**
     * @brief set plugin comment
     * @param _comment       comment
     */
    void setComment(const QString _comment);
    /**
     * @brief set plugin name
     * @param _name          plugin name
     */
    void setName(const QString _name);
    // settings
    /**
     * @brief application settings
     * @return configuration map
     */
    QVariantHash appConfiguration() const;
    /**
     * @brief init the plugin components
     * @remark this method will be called before TabPluginItem::init()
     * @param _core          pointer to core object
     * @param _settings      application settings
     */
    virtual void preinit(QuadroCore *_core, const QVariantHash _settings = QVariantHash());

public slots:
    /**
     * @brief init the plugin
     */
    virtual void init() = 0;
    /**
     * @brief quit from plugin
     */
    virtual void quit() = 0;
    /**
     * @brief read plugin settings from configuration file
     * @param _desktopPath   full path to settings file
     */
    virtual void readSettings(const QString _desktopPath) = 0;
    /**
     * @brief save plugin settings to configuration file
     * @param _desktopPath   full path to settings file
     * @return true if settings has been saved successfully
     * @return false if there was an error while settings sync
     */
    virtual bool saveSettings(const QString _desktopPath) = 0;

private:
    /**
     * @brief core object
     */
    QuadroCore *m_core = nullptr;
    // properties
    /**
     * @brief plugin API version. Default is 1
     */
    int m_api = 1;
    /**
     * @brief application settings
     */
    QVariantHash m_appConfiguration;
    /**
     * @brief plugin comment. Default is empty
     */
    QString m_comment = QString();
    /**
     * @brief plugin name. Default is "none"
     */
    QString m_name = QString("none");
    // methods
    /**
     * @brief create DBus session
     */
    void createDBusSession();
};

Q_DECLARE_INTERFACE(TabPluginItem, "core.quadro.tabplugin")


#endif /* TABPLUGINITEM_H */
