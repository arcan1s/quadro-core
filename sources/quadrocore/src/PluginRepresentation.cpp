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
 * @file PluginRepresentation.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadrocore/Quadro.h"

#include <QSettings>

using namespace Quadro;


/**
 * @class PluginRepresentation
 */
/**
 * @fn PluginRepresentation
 */
PluginRepresentation::PluginRepresentation(
    const QString &_author, const QString &_comment, const QString &_group,
    const QString &_location, const QString &_name, const QString &_url,
    const QString &_version, QObject *_parent)
    : QObject(_parent)
    , m_author(_author)
    , m_comment(_comment)
    , m_group(_group)
    , m_location(_location)
    , m_name(_name)
    , m_url(_url)
    , m_version(_version)
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;
}


/**
 * @fn ~PluginRepresentation
 */
PluginRepresentation::~PluginRepresentation()
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;
}


/**
 * @fn fromFile
 */
PluginRepresentation *PluginRepresentation::fromFile(const QString &_filePath,
                                                     QObject *_parent)
{
    qCDebug(LOG_LIB) << "Load metadata from file" << _filePath;

    QSettings settings(_filePath, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    QString group;
    QString configGroup;
    if (settings.childGroups().contains("Quadro plugin")) {
        group = "plugin";
        configGroup = "Quadro plugin";
    } else if (settings.childGroups().contains("Quadro tabplugin")) {
        group = "tabplugin";
        configGroup = "Quadro tabplugin";
    } else if (settings.childGroups().contains("Quadro genericplugin")) {
        group = "genericplugin";
        configGroup = "Quadro genericplugin";
    } else {
        qCWarning(LOG_LIB) << "No known group found";
        return nullptr;
    }

    settings.beginGroup(configGroup);
    QString author = settings.value("Author", "John Smith").toString();
    QString comment = settings.value("Comment", "").toString();
    QString name = settings.value("Name", "none").toString();
    QString url = settings.value("URL", "http://localhost").toString();
    QString version = settings.value("Version", "0.1").toString();
    settings.endGroup();

    return new PluginRepresentation(author, comment, group,
                                    QFileInfo(_filePath).absolutePath(), name,
                                    url, version, _parent);
}


/**
 * @fn author
 */
QString PluginRepresentation::author() const
{
    return m_author;
}


/**
 * @fn comment
 */
QString PluginRepresentation::comment() const
{
    return m_comment;
}


/**
 * @fn group
 */
QString PluginRepresentation::group() const
{
    return m_group;
}


/**
 * @fn location
 */
QString PluginRepresentation::location() const
{
    return m_location;
}


/**
 * @fn name
 */
QString PluginRepresentation::name() const
{
    return m_name;
}


/**
 * @fn url
 */
QString PluginRepresentation::url() const
{
    return m_url;
}


/**
 * @fn version
 */
QString PluginRepresentation::version() const
{
    return m_version;
}
