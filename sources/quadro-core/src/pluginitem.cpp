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


#include <QDBusConnection>
#include <QDBusMessage>
#include <QBuffer>
#include <QColor>
#include <QDBusConnection>
#include <QDebug>
#include <QSettings>

#include <quadro/quadro.h>
#include <pdebug/pdebug.h>

#include "version.h"


/**
 * @class PluginItem
 */
/**
 * @fn PluginItem
 */
PluginItem::PluginItem(QObject *parent, const bool debugCmd)
    : QObject(parent),
      debug(debugCmd)
{
    m_adaptor = new PluginAdaptor(this, debug);
    init();
}


/**
 * @fn ~PluginItem
 */
PluginItem::~PluginItem()
{
    if (debug) qDebug() << PDEBUG;

    removeSession();
    delete m_adaptor;
}


/**
 * @fn api
 */
int PluginItem::api()
{
    if (debug) qDebug() << PDEBUG;

    return m_api;
}


/**
 * @fn background
 */
QString PluginItem::background()
{
    if (debug) qDebug() << PDEBUG;

    return m_background;
}


/**
 * @fn comment
 */
QString PluginItem::comment()
{
    if (debug) qDebug() << PDEBUG;

    return m_comment;
}


/**
 * @fn configuration
 */
QMap<QString, QVariant> PluginItem::configuration()
{
    if (debug) qDebug() << PDEBUG;

    QMap<QString, QVariant> pluginSettings;
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
    if (debug) qDebug() << PDEBUG;

    return m_data;
}


/**
 * @fn setUi
 */
bool PluginItem::hasUi()
{
    if (debug) qDebug() << PDEBUG;

    return m_ui;
}


/**
 * @fn height
 */
int PluginItem::height()
{
    if (debug) qDebug() << PDEBUG;

    return m_height;
}


/**
 * @fn image
 */
QString PluginItem::htmlImage()
{
    if (debug) qDebug() << PDEBUG;

    PluginItem::ImageType type = defineImageType(background());
    QImage pluginImage;
    QString image;

    switch (type) {
    case PluginItem::Color:
        pluginImage.fill(background());
        image = convertImage(pluginImage);
        break;
    case PluginItem::Path:
        image = convertImage(pluginImage);
        break;
    case PluginItem::Hash:
        image = background();
        break;
    case PluginItem::None:
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
    if (debug) qDebug() << PDEBUG;

    return m_name;
}


/**
 * @fn path
 */
QString PluginItem::path()
{
    if (debug) qDebug() << PDEBUG;

    return m_path;
}


/**
 * @fn timer
 */
int PluginItem::timer()
{
    if (debug) qDebug() << PDEBUG;

    return m_timer;
}


/**
 * @fn width
 */
int PluginItem::width()
{
    if (debug) qDebug() << PDEBUG;

    return m_width;
}


/**
 * @fn setBackground
 */
void PluginItem::setBackground(QString _background)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Background" << _background;
    if (_background.isEmpty()) _background = QString("#ffffffff");

    m_background = _background;
}


/**
 * @fn setComment
 */
void PluginItem::setComment(const QString _comment)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Comment" << _comment;

    m_comment = _comment;
}


/**
 * @fn setHeight
 */
void PluginItem::setHeight(int _height)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Height" << _height;
    if (_height < 1) _height = 1;

    m_height = _height;
}


/**
 * @fn setWidth
 */
void PluginItem::setWidth(int _width)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Width" << _width;
    if (_width < 1) _width = 1;

    m_width = _width;
}


/**
 * @fn isDesktopPlugin
 */
bool PluginItem::isDesktopPlugin(const QString _desktopPath)
{
    QSettings settings(_desktopPath, QSettings::IniFormat);

    return settings.childGroups().contains(QString("[Desktop plugin]"));
}


/**
 * @fn readDesktop
 */
void PluginItem::readDesktop(const QString _desktopPath)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Path" << _desktopPath;

    QSettings settings(_desktopPath, QSettings::IniFormat);

    settings.beginGroup(QString("[Quadro plugin]"));
    setTimer(settings.value(QString("API"), m_api).toInt());
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
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Path" << _desktopPath;

    QSettings settings(_desktopPath, QSettings::IniFormat);

    settings.beginGroup(name());

    settings.beginGroup(QString("[Core]"));
    setComment(settings.value(QString("Comment"), m_comment).toString());
    setTimer(settings.value(QString("Timer"), m_timer).toInt());
    settings.endGroup();

    settings.beginGroup(QString("[UI]"));
    setHeight(settings.value(QString("Height"), m_height).toInt());
    setWidth(settings.value(QString("Width"), m_width).toInt());
    settings.endGroup();

    settings.endGroup();
}


/**
 * @fn saveSettings
 */
bool PluginItem::saveSettings(const QString _desktopPath)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Path" << _desktopPath;

    QMap<QString, QVariant> config = configuration();
    QSettings settings(_desktopPath, QSettings::IniFormat);

    settings.beginGroup(name());

    settings.beginGroup(QString("[Core]"));
    settings.setValue(QString("Comment"), config[QString("Comment")]);
    settings.setValue(QString("Timer"), config[QString("Timer")]);
    settings.endGroup();

    settings.beginGroup(QString("[UI]"));
    settings.setValue(QString("Height"), config[QString("Height")]);
    settings.setValue(QString("Width"), config[QString("Width")]);
    settings.endGroup();

    settings.endGroup();

    settings.sync();

    return settings.status() == QSettings::NoError;
}


/**
 * @fn createSession
 */
void PluginItem::createSession()
{
    if (debug) qDebug() << PDEBUG;

    QDBusConnection bus = QDBusConnection::sessionBus();
    if (!bus.registerObject(path(), m_adaptor, QDBusConnection::ExportAllSlots |
                            QDBusConnection::ExportAllSignals)) {
        if (debug) qDebug() << PDEBUG << ":" << "Could not register object";
        if (debug) qDebug() << PDEBUG << ":" << bus.lastError().message();
    }
    connect(this, SIGNAL(updated(QString)), this, SLOT(sendUpdateToDBus(QString)));
}


/**
 * @fn updateData
 */
void PluginItem::updateData()
{
    if (debug) qDebug() << PDEBUG;

    m_data = getData();
    m_background = getBackground();
    emit(updated(m_data));
}


/**
 * @fn sendUpdateToDBus
 */
void PluginItem::sendUpdateToDBus(const QString _data)
{
    if (debug) qDebug() << PDEBUG;

    return m_adaptor->UpdatesReceived(_data);
}


/**
 * @fn convertImage
 */
QString PluginItem::convertImage(const QImage _image)
{
    if (debug) qDebug() << PDEBUG;

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
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Source" << _source;

    PluginItem::ImageType type = PluginItem::None;
    QImage testImage;
    if (QColor::isValidColor(_source))
        type = PluginItem::Color;
    else if (testImage.load(_source))
        type = PluginItem::Path;
    else
        type = PluginItem::Hash;

    return type;
}


/**
 * @fn removeSession
 */
void PluginItem::removeSession()
{
    if (debug) qDebug() << PDEBUG;

    QDBusConnection::sessionBus().unregisterObject(path());
}


/**
 * @fn setApi
 */
void PluginItem::setApi(int _api)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "API version" << _api;
    if (_api < 1) _api = 1;
    if (_api > PLUGIN_API) _api = PLUGIN_API;

    m_api = _api;
}


/**
 * @fn setHasUi
 */
void PluginItem::setHasUi(const bool _hasUi)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Has UI" << _hasUi;

    m_ui = _hasUi;
}


/**
 * @fn setName
 */
void PluginItem::setName(const QString _name)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Name" << _name;

    m_name = _name;
}


/**
 * @fn setPath
 */
void PluginItem::setPath(QString _path)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Path" << _path;
    if (!_path.startsWith(QString("/"))) _path = QString("/%1").arg(_path);

    m_path = _path;
}


/**
 * @fn setTimer
 */
void PluginItem::setTimer(int _timer)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Timer" << _timer;
    if ((_timer >= 0) && (_timer < MINIMAL_TIMER)) _timer = MINIMAL_TIMER;

    m_timer = _timer;
}
