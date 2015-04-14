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


#include <QColor>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDebug>
#include <QtGui/qimage.h>

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
 * @fn data
 */
QString PluginItem::data()
{
    if (debug) qDebug() << PDEBUG;

    return m_data;
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
QImage PluginItem::image()
{
    if (debug) qDebug() << PDEBUG;

    QImage pluginImage;
    if (QColor::isValidColor(background()))
        // data is color
        pluginImage.fill(background());
    // if not try to load from file
    else if (!pluginImage.load(background()))
        // if could not load from file it will be loaded as from data
        pluginImage.loadFromData(background().toLatin1());

    return pluginImage;
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
 * @fn settings
 */
QMap<QString, QString> PluginItem::settings()
{
    if (debug) qDebug() << PDEBUG;

    QMap<QString, QString> pluginSettings;
    // TODO

    return pluginSettings;
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
void PluginItem::setBackground(const QString _background)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Background" << _background;

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
void PluginItem::setHeight(const int _height)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Height" << _height;

    m_height = _height;
}


/**
 * @fn setWidth
 */
void PluginItem::setWidth(const int _width)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Width" << _width;

    m_width = _width;
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
 * @fn createSession
 */
void PluginItem::createSession()
{
    if (debug) qDebug() << PDEBUG;

    QDBusConnection bus = QDBusConnection::sessionBus();
    if (!bus.registerObject(path(), m_adaptor,
                            QDBusConnection::ExportAllContents)) {
        if (debug) qDebug() << PDEBUG << ":" << "Could not register object";
        if (debug) qDebug() << PDEBUG << ":" << bus.lastError().message();
    }
}


void PluginItem::updateData()
{
    if (debug) qDebug() << PDEBUG;

    m_data = getData();
    emit(updated(m_data));
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
void PluginItem::setTimer(const int _timer)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Timer" << _timer;

    m_timer = _timer;
}
