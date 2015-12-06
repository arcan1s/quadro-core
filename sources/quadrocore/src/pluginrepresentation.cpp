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
 * @file pluginrepresentation.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */

#include "quadrocore/quadro.h"

#include <QSettings>


/**
 * @class PluginRepresentation
 */
/**
 * @fn PluginRepresentation
 */
PluginRepresentation::PluginRepresentation(const QString comment, const QString group,
                                           const QString location, const QString name,
                                           QObject *parent)
    : QObject(parent)
    , m_comment(comment)
    , m_group(group)
    , m_location(location)
    , m_name(name)
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
PluginRepresentation *PluginRepresentation::fromFile(const QString _filePath,
                                                     QObject *_parent)
{
    qCDebug(LOG_LIB) << "Load metadata from file" << _filePath;

    QSettings settings(_filePath, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    QString group;
    QString configGroup;
    if (settings.childGroups().contains(QString("Quadro plugin"))) {
        group = QString("plugin");
        configGroup = QString("Quadro plugin");
    } else if (settings.childGroups().contains(QString("Quadro tabplugin"))) {
        group = QString("tabplugin");
        configGroup = QString("Quadro tabplugin");
    } else if (settings.childGroups().contains(QString("Quadro genericplugin"))) {
        group = QString("genericplugin");
        configGroup = QString("Quadro genericplugin");
    } else {
        qCWarning(LOG_LIB) << "No known group found";
        return nullptr;
    }

    settings.beginGroup(configGroup);
    QString comment = settings.value(QString("Comment"), QString("")).toString();
    QString name = settings.value(QString("Name"), QString("none")).toString();
    settings.endGroup();

    return new PluginRepresentation(comment, group,
                                    QFileInfo(_filePath).absolutePath(), name,
                                    _parent);
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
