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

#include <QtPlugin>
#include <QWidget>


/**
 * @brief The TabPluginItem class provides core part of plugin run in different tab
 */
class TabPluginItem : public QObject
{
    Q_OBJECT
    // core properties
    Q_PROPERTY(int api READ api WRITE setApi)
    Q_PROPERTY(QString comment READ comment WRITE setComment)
    Q_PROPERTY(QString name READ name WRITE setName)
    // ui properties
    Q_PROPERTY(QString background READ background WRITE setBackground)
    Q_PROPERTY(QString htmlImage READ htmlImage)

public:
    /**
     * @brief TabPluginItem class constructor
     * @param parent         pointer to parent item
     * @param debugCmd       show debug messages
     */
    explicit TabPluginItem(QObject *parent, const bool debugCmd = false);
    /**
     * @brief TabPluginItem class destructor
     */
    ~TabPluginItem();
    // get methods
    /**
     * @brief plugin API version
     * @return API version
     */
    int api();
    /**
     * @brief plugin background
     * @return background
     */
    QString background();
    /**
     * @brief plugin comment
     * @return comment
     */
    QString comment();
    /**
     * @brief plugin current settings which will be applied on next start
     * @return configuration map
     */
    QMap<QString, QVariant> configuration();
    /**
     * @brief plugin UI image. It fills from background()
     * @return valid HTML image as text
     */
    QString htmlImage();
    /**
     * @brief plugin name
     * @return name
     */
    QString name();
    /**
     * @brief plugin ui
     * @return pointer to QWidget part of the ui.
     */
    QWidget *ui();
    // set methods
    /**
     * @brief set plugin background
     * @param _background    background. May be color in valid format or path to
     *                       image. Default is #ffffffff
     */
    void setBackground(QString _background = QString("#ffffffff"));
    /**
     * @brief set plugin comment
     * @param _comment       comment
     */
    void setComment(const QString _comment);

public slots:
    /**
     * @brief quit from plugin
     */
    virtual void quit();
    /**
     * @brief read plugin information from desktop file
     * @param _desktopPath   full path to desktop file
     */
    void readDesktop(const QString _desktopPath);
    /**
     * @brief read plugin settings from configuration file
     * @param _desktopPath   full path to settings file
     */
    void readSettings(const QString _desktopPath);
    /**
     * @brief save plugin settings to configuration file
     * @param _desktopPath   full path to settings file
     * @return true if settings has been saved successfully
     * @return false if there was an error while settings sync
     */
    bool saveSettings(const QString _desktopPath);

private:
    /**
     * @brief show debug messages. Default is false
     */
    bool debug = false;
    // properties
    /**
     * @brief plugin API version. Default is 1
     */
    int m_api = 1;
    /**
     * @brief plugin background. May be color or path to image. Default is empty
     */
    QString m_background = QString();
    /**
     * @brief plugin comment. Default is empty
     */
    QString m_comment = QString();
    /**
     * @brief plugin name. Default is "none"
     */
    QString m_name = QString("none");
    /**
     * @brief has the plugin UI or not. Default is false
     */
    QWidget *m_ui = nullptr;
    // methods
    /**
     * @brief init the plugin. May be implemented by derivative class
     */
    virtual void init();
    // private set methods
    /**
     * @brief set API version
     * @param _api           plugin API version
     */
    void setApi(int _api = 1);
    /**
     * @brief set plugin name
     * @param _name          plugin name
     */
    void setName(const QString _name);
};

Q_DECLARE_INTERFACE(TabPluginItem, "org.quadro.plugin")


#endif /* PLUGINITEM_H */
