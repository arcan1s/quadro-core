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
 * @file pluginadaptor.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadro/quadro.h"


/**
 * @class PluginAdaptor
 */
/**
 * @fn PluginAdaptor
 */
PluginAdaptor::PluginAdaptor(PluginItem *plugin)
    : QDBusAbstractAdaptor(plugin),
      m_plugin(plugin)
{
    qCDebug(LOG_PL) << __PRETTY_FUNCTION__;
}


/**
 * @fn ~PluginAdaptor
 */
PluginAdaptor::~PluginAdaptor()
{
    qCDebug(LOG_PL) << __PRETTY_FUNCTION__;
}


/**
 * @fn Ping
 */
bool PluginAdaptor::Ping()
{
    return true;
}


/**
 * @fn Api
 */
int PluginAdaptor::Api()
{
    return m_plugin->api();
}


/**
 * @fn Background
 */
QString PluginAdaptor::Background()
{
    return m_plugin->background();
}


/**
 * @fn Comment
 */
QString PluginAdaptor::Comment()
{
    return m_plugin->comment();
}


/**
 * @fn Configuration
 */
QStringList PluginAdaptor::Configuration()
{
    QVariantMap configMap = m_plugin->configuration();
    QStringList output;
    for (int i=0; i<configMap.keys().count(); i++) {
        QString key = configMap.keys()[i];
        QString value = configMap[key].toString();
        output.append(QString("%1=%2").arg(key).arg(value));
    }

    return output;
}


/**
 * @fn Data
 */
QString PluginAdaptor::Data()
{
    return m_plugin->data();
}


/**
 * @fn HasUi
 */
bool PluginAdaptor::HasUi()
{
    return m_plugin->hasUi();
}


/**
 * @fn Height
 */
int PluginAdaptor::Height()
{
    return m_plugin->height();
}


/**
 * @fn HtmlImage
 */
QString PluginAdaptor::HtmlImage()
{
    return m_plugin->htmlImage();
}


/**
 * @fn Name
 */
QString PluginAdaptor::Name()
{
    return m_plugin->name();
}


/**
 * @fn Timer
 */
int PluginAdaptor::Timer()
{
    return m_plugin->timer();
}


/**
 * @fn Width
 */
int PluginAdaptor::Width()
{
    return m_plugin->width();
}


/**
 * @fn Action
 */
void PluginAdaptor::Action()
{
    return m_plugin->actionRequired();
}


/**
 * @fn Close
 */
void PluginAdaptor::Close()
{
    return m_plugin->quit();
}


/**
 * @fn ReadDesktop
 */
void PluginAdaptor::ReadDesktop(const QString desktopPath)
{
    return m_plugin->readDesktop(desktopPath);
}


/**
 * @fn ReadSettings
 */
void PluginAdaptor::ReadSettings(const QString desktopPath)
{
    return m_plugin->readSettings(desktopPath);
}


/**
 * @fn SaveSettings
 */
bool PluginAdaptor::SaveSettings(const QString desktopPath)
{
    return m_plugin->saveSettings(desktopPath);
}


/**
 * @fn Start
 */
void PluginAdaptor::Start(const bool start)
{
    if (start)
        return m_plugin->startTimer();
    else
        return m_plugin->stopTimer();
}


/**
 * @fn Update
 */
void PluginAdaptor::Update()
{
    return m_plugin->updateData();
}


/**
 * @fn UpdatesReceived
 */
void PluginAdaptor::UpdatesReceived(const QString data)
{
    emit(Updated(data));
}
