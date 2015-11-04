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
 * @file tabpluginitem.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadro/quadro.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QSettings>


/**
 * @class TabPluginItem
 */
/**
 * @fn TabPluginItem
 */
//TabPluginItem::TabPluginItem(QWidget *parent)
//    : QMainWindow(parent)
//{
//    qCDebug(LOG_PL) << __PRETTY_FUNCTION__;
//}


/**
 * @fn ~TabPluginItem
 */
TabPluginItem::~TabPluginItem()
{
    qCDebug(LOG_PL) << __PRETTY_FUNCTION__;

    QDBusConnection::sessionBus().unregisterObject(QString("/%1").arg(m_name));
    QDBusConnection::sessionBus().unregisterService(DBUS_PLUGIN_SERVICE);
}


/**
 * @fn api
 */
int TabPluginItem::api() const
{
    return m_api;
}


/**
 * @fn comment
 */
QString TabPluginItem::comment() const
{
    return m_comment;
}


/**
 * @fn core
 */
QuadroCore *TabPluginItem::core()
{
    return m_core;
}


/**
 * @fn name
 */
QString TabPluginItem::name() const
{
    return m_name;
}


/**
 * @fn setApi
 */
void TabPluginItem::setApi(int _api)
{
    qCDebug(LOG_PL) << "API version" << _api;
    if (_api < 1) _api = 1;
    if (_api > TAB_PLUGIN_API) _api = TAB_PLUGIN_API;

    m_api = _api;
}


/**
 * @fn setComment
 */
void TabPluginItem::setComment(const QString _comment)
{
    qCDebug(LOG_PL) << "Comment" << _comment;

    m_comment = _comment;
}


/**
 * @fn setName
 */
void TabPluginItem::setName(const QString _name)
{
    qCDebug(LOG_PL) << "Name" << _name;

    m_name = _name;
}


/**
 * @fn appConfiguration
 */
QVariantHash TabPluginItem::appConfiguration() const
{
    return m_appConfiguration;
}


/**
 * @fn preinit
 */
void TabPluginItem::preinit(QuadroCore *_core, const QVariantHash _settings)
{
    qCDebug(LOG_PL) << "Application settings" << _settings;

    m_core = _core;
    m_appConfiguration = _settings;
    createDBusSession();
}


/**
 * @fn readDesktop
 */
QVariantHash TabPluginItem::readDesktop(const QString _desktopPath)
{
    qCDebug(LOG_PL) << "Path" << _desktopPath;

    QVariantHash pluginData;
    QSettings settings(_desktopPath, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    if (!settings.childGroups().contains(QString("Quadro tabplugin")))
        return pluginData;

    settings.beginGroup(QString("Quadro tabplugin"));
    pluginData[QString("API")] = settings.value(QString("API"), TAB_PLUGIN_API);
    pluginData[QString("Comment")] = settings.value(QString("Comment"), QString(""));
    pluginData[QString("Name")] = settings.value(QString("Name"), QString("none"));
    settings.endGroup();

    return pluginData;
}


/**
 * @fn createDBusSession
 */
void TabPluginItem::createDBusSession()
{
    QDBusConnection bus = QDBusConnection::sessionBus();
    if (!bus.registerService(DBUS_PLUGIN_SERVICE)) {
        qCWarning(LOG_UI) << "Could not register service";
        qCWarning(LOG_UI) << bus.lastError().message();
    }
    if (!bus.registerObject(QString("/%1").arg(m_name),
                            new TabPluginAdaptor(this),
                            QDBusConnection::ExportAllContents)) {
        qCWarning(LOG_UI) << "Could not register library object";
        qCWarning(LOG_UI) << bus.lastError().message();
    }
}
