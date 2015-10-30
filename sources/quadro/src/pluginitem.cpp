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
 * @file pluginitem.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadro/quadro.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QBuffer>
#include <QColor>
#include <QDBusConnection>
#include <QDebug>
#include <QSettings>


/**
 * @class PluginItem
 */
/**
 * @fn PluginItem
 */
PluginItem::PluginItem(QObject *parent)
    : QObject(parent)
{
    qSetMessagePattern(LOG_FORMAT);
    qCDebug(LOG_PL) << __PRETTY_FUNCTION__;
    foreach (const QString metadata, getBuildData())
        qCDebug(LOG_PL) << metadata;

    init();
}


/**
 * @fn ~PluginItem
 */
PluginItem::~PluginItem()
{
    qCDebug(LOG_PL) << __PRETTY_FUNCTION__;

    removeSession();
    delete m_adaptor;
    delete m_timerItem;
}


/**
 * @fn api
 */
int PluginItem::api()
{
    return m_api;
}


/**
 * @fn background
 */
QString PluginItem::background()
{
    return m_background;
}


/**
 * @fn comment
 */
QString PluginItem::comment()
{
    return m_comment;
}


/**
 * @fn configuration
 */
QVariantHash PluginItem::configuration()
{
    QVariantHash pluginSettings;
    pluginSettings[QString("Comment")] = comment();
    pluginSettings[QString("Height")] = height();
    pluginSettings[QString("Timer")] = timer();
    pluginSettings[QString("Width")] = width();

    return pluginSettings;
}


/**
 * @fn data
 */
QString PluginItem::data()
{
    return m_data;
}


/**
 * @fn setUi
 */
bool PluginItem::hasUi()
{
    return m_ui;
}


/**
 * @fn height
 */
int PluginItem::height()
{
    return m_height;
}


/**
 * @fn htmlImage
 */
QString PluginItem::htmlImage()
{
    PluginItem::ImageType type = defineImageType(background());
    QImage pluginImage;
    QString image;

    switch (type) {
    case ImageType::COLOR:
        pluginImage.fill(background());
        image = convertImage(pluginImage);
        break;
    case ImageType::PATH:
        image = convertImage(pluginImage);
        break;
    case ImageType::HASH:
        image = background();
        break;
    case ImageType::NONE:
    default:
        break;
    }

    return image;
}


/**
 * @fn name
 */
QString PluginItem::name()
{
    return m_name;
}


/**
 * @fn path
 */
QString PluginItem::path()
{
    return m_path;
}


/**
 * @fn timer
 */
int PluginItem::timer()
{
    return m_timer;
}


/**
 * @fn width
 */
int PluginItem::width()
{
    return m_width;
}


/**
 * @fn setBackground
 */
void PluginItem::setBackground(QString _background)
{
    qCDebug(LOG_PL) << "Background" << _background;
    if (_background.isEmpty()) _background = QString("#ffffffff");

    m_background = _background;
}


/**
 * @fn setComment
 */
void PluginItem::setComment(const QString _comment)
{
    qCDebug(LOG_PL) << "Comment" << _comment;

    m_comment = _comment;
}


/**
 * @fn setHeight
 */
void PluginItem::setHeight(int _height)
{
    qCDebug(LOG_PL) << "Height" << _height;
    if (_height < 1) _height = 1;

    m_height = _height;
}


/**
 * @fn setWidth
 */
void PluginItem::setWidth(int _width)
{
    qCDebug(LOG_PL) << "Width" << _width;
    if (_width < 1) _width = 1;

    m_width = _width;
}


/**
 * @fn readDesktop
 */
void PluginItem::readDesktop(const QString _desktopPath)
{
    qCDebug(LOG_PL) << "Path" << _desktopPath;

    QSettings settings(_desktopPath, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");

    settings.beginGroup(QString("Quadro plugin"));
    setApi(settings.value(QString("API"), m_api).toInt());
    setComment(settings.value(QString("Comment"), m_comment).toString());
    setPath(settings.value(QString("DBusPath"), m_path).toString());
    setHasUi(settings.value(QString("HasUi"), m_ui).toBool());
    setName(settings.value(QString("Name"), m_name).toString());
    setTimer(settings.value(QString("Timer"), m_timer).toInt());
    settings.endGroup();
}


/**
 * @fn readSettings
 */
void PluginItem::readSettings(const QString _desktopPath)
{
    qCDebug(LOG_PL) << "Path" << _desktopPath;

    QSettings settings(_desktopPath, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");

    settings.beginGroup(name());

    settings.beginGroup(QString("Core"));
    setComment(settings.value(QString("Comment"), m_comment).toString());
    setTimer(settings.value(QString("Timer"), m_timer).toInt());
    settings.endGroup();

    settings.beginGroup(QString("UI"));
    setHeight(settings.value(QString("Height"), m_height).toInt());
    setWidth(settings.value(QString("Width"), m_width).toInt());
    settings.endGroup();

    settings.endGroup();
}


/**
 * @fn removeSession
 */
void PluginItem::removeSession()
{
    QDBusConnection::sessionBus().unregisterObject(path());
    delete m_adaptor;
    m_adaptor = nullptr;
}


/**
 * @fn saveSettings
 */
bool PluginItem::saveSettings(const QString _desktopPath)
{
    qCDebug(LOG_PL) << "Path" << _desktopPath;

    QVariantHash config = configuration();
    QSettings settings(_desktopPath, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");

    settings.beginGroup(name());

    settings.beginGroup(QString("Core"));
    settings.setValue(QString("Comment"), config[QString("Comment")]);
    settings.setValue(QString("Timer"), config[QString("Timer")]);
    settings.endGroup();

    settings.beginGroup(QString("UI"));
    settings.setValue(QString("Height"), config[QString("Height")]);
    settings.setValue(QString("Width"), config[QString("Width")]);
    settings.endGroup();

    settings.endGroup();

    settings.sync();

    return settings.status() == QSettings::NoError;
}


/**
 * @fn startTimer
 */
void PluginItem::startTimer()
{
    if (timer() <= 0) return;

    m_timerItem = new QTimer(this);
    m_timerItem->setInterval(timer());
    m_timerItem->setSingleShot(false);
    connect(m_timerItem, SIGNAL(timeout()), this, SLOT(updateData()));

    m_timerItem->start();
}


/**
 * @fn stopTimer
 */
void PluginItem::stopTimer()
{
    if (m_timerItem == nullptr) return;

    disconnect(m_timerItem, SIGNAL(timeout()), this, SLOT(updateData()));
    delete m_timerItem;
    m_timerItem = nullptr;
}


/**
 * @fn createSession
 */
void PluginItem::createSession()
{
    m_adaptor = new PluginAdaptor(this);
    QDBusConnection bus = QDBusConnection::sessionBus();
    if (!bus.registerObject(path(), m_adaptor, QDBusConnection::ExportAllSlots |
                            QDBusConnection::ExportAllSignals)) {
        qCCritical(LOG_PL) << "Could not register object";
        qCCritical(LOG_PL) << bus.lastError().message();
    }
    connect(this, SIGNAL(updated(QString)), this, SLOT(sendUpdateToDBus(QString)));
}


/**
 * @fn updateData
 */
void PluginItem::updateData()
{
    m_data = getData();
    m_background = getBackground();
    emit(updated(m_data));
}


/**
 * @fn sendUpdateToDBus
 */
void PluginItem::sendUpdateToDBus(const QString _data)
{
    qCDebug(LOG_PL) << "Data" << _data;

    return m_adaptor->UpdatesReceived(_data);
}


/**
 * @fn convertImage
 */
QString PluginItem::convertImage(const QImage _image)
{
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    _image.save(&buffer, "PNG");

    return byteArray.toBase64();
}


/**
 * @fn defineImageType
 */
PluginItem::ImageType PluginItem::defineImageType(const QString _source)
{
    qCDebug(LOG_PL) << "Source" << _source;

    PluginItem::ImageType type = ImageType::NONE;
    QImage testImage;
    if (QColor::isValidColor(_source))
        type = ImageType::COLOR;
    else if (testImage.load(_source))
        type = ImageType::PATH;
    else
        type = ImageType::HASH;

    return type;
}


/**
 * @fn setApi
 */
void PluginItem::setApi(int _api)
{
    qCDebug(LOG_PL) << "API version" << _api;
    if (_api < 1) _api = 1;
    if (_api > PLUGIN_API) _api = PLUGIN_API;

    m_api = _api;
}


/**
 * @fn setHasUi
 */
void PluginItem::setHasUi(const bool _hasUi)
{
    qCDebug(LOG_PL) << "Has UI" << _hasUi;

    m_ui = _hasUi;
}


/**
 * @fn setName
 */
void PluginItem::setName(const QString _name)
{
    qCDebug(LOG_PL) << "Name" << _name;

    m_name = _name;
}


/**
 * @fn setPath
 */
void PluginItem::setPath(QString _path)
{
    qCDebug(LOG_PL) << "Path" << _path;
    if (!_path.startsWith(QString("/"))) _path = QString("/%1").arg(_path);

    m_path = _path;
}


/**
 * @fn setTimer
 */
void PluginItem::setTimer(int _timer)
{
    qCDebug(LOG_PL) << "Timer" << _timer;
    if ((_timer >= 0) && (_timer < MINIMAL_TIMER)) _timer = MINIMAL_TIMER;

    m_timer = _timer;
}
