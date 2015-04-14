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
 * @file pluginitem.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef PLUGINITEM_H
#define PLUGINITEM_H

#include <QImage>
#include <QMap>
#include <QObject>


class PluginAdaptor;

/**
 * @brief The PluginItem class provides plugin core part
 */
class PluginItem : public QObject
{
    Q_OBJECT
    // core properties
    Q_PROPERTY(int api READ api)
    Q_PROPERTY(QString comment READ comment WRITE setComment)
    Q_PROPERTY(QString data READ data)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString path READ path WRITE setPath)
    Q_PROPERTY(int timer READ timer WRITE setTimer)
    // ui properties
    Q_PROPERTY(QString background READ background WRITE setBackground)
    Q_PROPERTY(int height READ height WRITE setHeight)
    Q_PROPERTY(QImage image READ image)
    Q_PROPERTY(int width READ width WRITE setWidth)

public:
    /**
     * @brief PluginItem class constructor
     * @param parent         pointer to parent item
     * @param name           plugin name
     * @param debugCmd       show debug messages
     */
    explicit PluginItem(QObject *parent, const bool debugCmd = false);
    /**
     * @brief PluginItem class destructor
     */
    ~PluginItem();
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
     * @brief plugin data in text
     * @return data
     */
    QString data();
    /**
     * @brief plugin UI height
     * @return height in UI grids
     */
    int height();
    /**
     * @brief plugin UI image. It fills from background()
     * @return QImage object
     */
    QImage image();
    /**
     * @brief plugin name
     * @return name
     */
    QString name();
    /**
     * @brief path in the DBus interface
     * @return DBus path
     */
    QString path();
    /**
     * @brief plugin current settings which will be applied on next start
     * @return map of settings
     */
    QMap<QString, QString> settings();
    /**
     * @brief plugin events timer
     * @return plugin timer in milliseconds
     */
    int timer();
    /**
     * @brief plugin UI width
     * @return width in UI grids
     */
    int width();
    // set methods
    /**
     * @brief set plugin background
     * @param _background    background. May be color in valid format or path to
     *                       image. Default is #ffffffff
     */
    void setBackground(const QString _background = QString("#ffffffff"));
    /**
     * @brief set plugin comment
     * @param _comment       comment
     */
    void setComment(const QString _comment);
    /**
     * @brief set plugin UI height
     * @param _height        plugin height in UI grid
     */
    void setHeight(const int _height);
    /**
     * @brief set plugin UI width
     * @param _width         plugin width in UI grid
     */
    void setWidth(const int _width);

signals:
    /**
     * @brief send if data updated
     */
    void updated(QString _data);

public slots:
    /**
     * @brief create plugin DBus session
     */
    void createSession();
    /**
     * @brief read plugin information from desktop file
     * @param _desktopPath   full path to desktop file
     */
    void readDesktop(const QString _desktopPath);
    /**
     * @brief read plugin settings from desktop file
     * @param _desktopPath   full path to settings file
     */
    void readSettings(const QString _desktopPath);
    /**
     * @brief update data. May be called to force update
     */
    void updateData();

private:
    /**
     * @brief show debug messages. Default is false
     */
    bool debug = false;
    // properties
    /**
     * @brief plugin adaptor
     */
    PluginAdaptor *m_adaptor = nullptr;
    /**
     * @brief plugin API version
     */
    int m_api = 1;
    /**
     * @brief plugin background. May be color or path to image
     */
    QString m_background;
    /**
     * @brief plugin comment
     */
    QString m_comment;
    /**
     * @brief cached data
     */
    QString m_data;
    /**
     * @brief plugin height in UI grids
     */
    int m_height;
    /**
     * @brief plugin name
     */
    QString m_name;
    /**
     * @brief path in the DBus interface
     */
    QString m_path;
    /**
     * @brief plugin timer in milliseconds
     */
    int m_timer;
    /**
     * @brief plugin width in UI grids
     */
    int m_width;
    // methods
    /**
     * @brief init the plugin if required
     */
    virtual void init();
    /**
     * @brief remove plugin DBus session
     */
    void removeSession();
    /**
     * @brief get data from source
     * @return new data
     */
    virtual QString getData();
    // private set methods
    /**
     * @brief set plugin name
     * @param _name          plugin name
     */
    void setName(const QString _name);
    /**
     * @brief set path to the plugin in the DBus interface
     * @param _path          path to the plugin
     */
    void setPath(QString _path);
    /**
     * @brief set timer for events
     * @param _timer         plugin timer in milliseconds
     */
    void setTimer(const int _timer);
};


#endif /* PLUGINITEM_H */
