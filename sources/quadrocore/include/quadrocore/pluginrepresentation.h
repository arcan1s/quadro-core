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
 * @file pluginrepresentation.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef PLUGINREPRESENTATION_H
#define PLUGINREPRESENTATION_H

#include <QObject>


/**
 * @brief The PluginRepresentation class provides common plugin information
 */
class PluginRepresentation : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString author READ author)
    Q_PROPERTY(QString comment READ comment)
    Q_PROPERTY(QString group READ group)
    Q_PROPERTY(QString location READ location)
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString url READ url)
    Q_PROPERTY(QString version READ version)

public:
    /**
     * @brief PluginRepresentation class constructor
     * @param author         plugin author
     * @param comment        plugin comment
     * @param group          plugin group
     * @param location       plugin location
     * @param name           plugin name
     * @param url            plugin url
     * @param version        plugin version
     * @param parent         pointer to parent item
     */
    explicit PluginRepresentation(const QString author, const QString comment,
                                  const QString group, const QString location,
                                  const QString name, const QString url,
                                  const QString version,
                                  QObject *parent = nullptr);
    /**
     * @brief PluginRepresentation class destructor
     */
    virtual ~PluginRepresentation();
    /**
     * @brief init object from metadata file
     * @param _filePath      path to configuration file
     * @param _parent        pointer to parent object
     * @return initialized object
     */
    static PluginRepresentation *fromFile(const QString _filePath,
                                          QObject *_parent = nullptr);
    /**
     * @brief plugin author
     * @return plugin author
     */
    QString author() const;
    /**
     * @brief plugin comment
     * @return plugin comment
     */
    QString comment() const;
    /**
     * @brief plugin group
     * @return plugin group
     */
    QString group() const;
    /**
     * @brief plugin location
     * @return plugin location
     */
    QString location() const;
    /**
     * @brief plugin name
     * @return plugin name
     */
    QString name() const;
    /**
     * @brief plugin url
     * @return plugin url
     */
    QString url() const;
    /**
     * @brief plugin version
     * @return plugin version
     */
    QString version() const;

private:
    /**
     * @brief plugin author
     */
    QString m_author;
    /**
     * @brief plugin comment
     */
    QString m_comment;
    /**
     * @brief plugin group
     */
    QString m_group;
    /**
     * @brief plugin location
     */
    QString m_location;
    /**
     * @brief plugin name
     */
    QString m_name;
    /**
     * @brief plugin url
     */
    QString m_url;
    /**
     * @brief plugin version
     */
    QString m_version;
};


#endif /* PLUGINREPRESENTATION_H */
