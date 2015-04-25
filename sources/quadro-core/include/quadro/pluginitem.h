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

#include <QtPlugin>
#include <QTimer>


class PluginAdaptor;

/**
 * @brief The PluginItem class provides plugin core part
 */
class PluginItem : public QObject
{
    Q_OBJECT
    // core properties
    Q_PROPERTY(int api READ api WRITE setApi)
    Q_PROPERTY(QString comment READ comment WRITE setComment)
    Q_PROPERTY(QString data READ data)
    Q_PROPERTY(bool ui READ hasUi WRITE setHasUi)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString path READ path WRITE setPath)
    Q_PROPERTY(int timer READ timer WRITE setTimer)
    // ui properties
    Q_PROPERTY(QString background READ background WRITE setBackground)
    Q_PROPERTY(int height READ height WRITE setHeight)
    Q_PROPERTY(QString htmlImage READ htmlImage)
    Q_PROPERTY(int width READ width WRITE setWidth)

public:
    /**
     * @brief PluginItem class constructor
     * @param parent         pointer to parent item
     * @param debugCmd       show debug messages
     */
    explicit PluginItem(QObject *parent, const bool debugCmd = false);
    /**
     * @brief PluginItem class destructor
     */
    ~PluginItem();
    // enums
    /**
     * @enum ImageType
     * @brief image type defined from string
     * @var ImageType::None
     * type is not defined
     * @var ImageType::Color
     * the string is a valid Qt color
     * @var ImageType::Path
     * the string is path to image
     * @var ImageType::Hash
     * the string is a hash
     */
    enum ImageType {
        None = 0,
        Color,
        Path,
        Hash
    };
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
     * @brief plugin data in text
     * @return data
     */
    QString data();
    /**
     * @brief has plugin UI or not
     * @return true if it has one
     * @return false it it hasn't UI
     */
    bool hasUi();
    /**
     * @brief plugin UI height
     * @return height in UI grids
     */
    int height();
    /**
     * @brief plugin UI image. It fills from background()
     * @return QImage object
     */
    QString htmlImage();
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
     * @brief plugin events timer
     * @return plugin timer in milliseconds. May be more than MINIMAL_TIMER or
     * less than 0 in case of skiping automatic update
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
    void setBackground(QString _background = QString("#ffffffff"));
    /**
     * @brief set plugin comment
     * @param _comment       comment
     */
    void setComment(const QString _comment);
    /**
     * @brief set plugin UI height
     * @param _height        plugin height in UI grid
     */
    void setHeight(int _height);
    /**
     * @brief set plugin UI width
     * @param _width         plugin width in UI grid
     */
    void setWidth(int _width);

signals:
    /**
     * @brief send if data has been updated
     * @param _data          updated data
     */
    void updated(const QString _data);

public slots:
    /**
     * @brief called if plugin has been clicked
     */
    virtual void actionRequired();
    /**
     * @brief create plugin DBus session
     */
    void createSession();
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
     * @brief remove plugin DBus session
     */
    void removeSession();
    /**
     * @brief save plugin settings to configuration file
     * @param _desktopPath   full path to settings file
     * @return true if settings has been saved successfully
     * @return false if there was an error while settings sync
     */
    bool saveSettings(const QString _desktopPath);
    /**
     * @brief start plugin timer
     */
    void startTimer();
    /**
     * @brief stop plugin timer
     */
    void stopTimer();
    /**
     * @brief update data. May be called to force update
     */
    void updateData();

private slots:
    /**
     * @brief send updated signal to DBus interface
     * @param _data          updated data
     */
    void sendUpdateToDBus(const QString _data);

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
     * @brief cached data
     */
    QString m_data;
    /**
     * @brief plugin height in UI grids. Default is 1
     */
    int m_height = 1;
    /**
     * @brief plugin name. Default is "none"
     */
    QString m_name = QString("none");
    /**
     * @brief path in the DBus interface. Default is m_name
     */
    QString m_path = QString();
    /**
     * @brief plugin timer in milliseconds. Default is 0
     */
    int m_timer = 0;
    /**
     * @brief plugin timer item
     */
    QTimer *m_timerItem = nullptr;
    /**
     * @brief has the plugin UI or not. Default is false
     */
    bool m_ui = false;
    /**
     * @brief plugin width in UI grids. Default is 1
     */
    int m_width = 1;
    // methods
    /**
     * @brief convert image from native QImage type to valid hash
     * @param _image         source image
     * @return image hash
     */
    QString convertImage(const QImage _image);
    /**
     * @brief define image type from given string
     * @param _source        image source
     * @return valid image type
     */
    ImageType defineImageType(const QString _source);
    /**
     * @brief init the plugin. May be implemented by derivative class
     */
    virtual void init();
    /**
     * @brief update image from source
     * @return new background
     */
    virtual QString getBackground();
    /**
     * @brief update data from source. Should be implemented by any derivative
     * class
     * @return new data
     */
    virtual QString getData();
    // private set methods
    /**
     * @brief set API version
     * @param _api           plugin API version
     */
    void setApi(int _api = 1);
    /**
     * @brief set has plugin UI or not
     * @param _hasUi         has plugin UI or not
     */
    void setHasUi(const bool _hasUi);
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
     * @param _timer         plugin timer in milliseconds. Should be more than
     *                       MINIMAL_TIMER or less than 0 (skip automatic update)
     */
    void setTimer(int _timer);
};

Q_DECLARE_INTERFACE(PluginItem, "org.quadro.plugin")


#endif /* PLUGINITEM_H */
