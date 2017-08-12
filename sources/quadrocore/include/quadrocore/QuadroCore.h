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
 * @file QuadroCore.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef QUADROCORE_H
#define QUADROCORE_H

#include <QObject>
#include <QVariant>


/**
 * @namespace Quadro
 */
namespace Quadro
{
class ConfigManager;

class DesktopInterface;

class DocumentsCore;

class FavoritesCore;

class FileManagerCore;

class LauncherCore;

class PluginCore;

class RecentlyCore;

/**
 * @brief The QuadroCore class provides Quadro backend
 */
class QuadroCore : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief QuadroCore class constructor
     * @param _parent pointer to parent item
     */
    explicit QuadroCore(QObject *_parent);

    /**
     * @brief QuadroCore class destructor
     */
    virtual ~QuadroCore();

    /**
     * @brief configuration manager object
     * @return pointer to configuration manager object
     */
    ConfigManager *config();

    /**
     * @brief documents core object
     * @return pointer to documents core object
     */
    DocumentsCore *documents();

    /**
     * @brief favorites core object
     * @return pointer to favorites core object
     */
    FavoritesCore *favorites();

    /**
     * @brief filemanager core object
     * @return pointer to filemanager core object
     */
    FileManagerCore *filemanager();

    /**
     * @brief launcher core object
     * @return pointer to launcher core object
     */
    LauncherCore *launcher();

    /**
     * @brief platform plugin object
     * @return pointer to DesktopInterface or nullptr if no objects found
     */
    DesktopInterface *platformPlugin();

    /**
     * @brief plugin core object
     * @return pointer to plugin core object
     */
    PluginCore *plugin();

    /**
     * @brief recently core object
     * @return pointer to recently core object
     */
    RecentlyCore *recently();

private:
    /**
     * @brief create DBus session
     */
    void createDBusSession();

    /**
     * @brief init platform depended plugin
     */
    void initPlatformPlugin();

    /**
     * @fn configuration manager object
     */
    ConfigManager *m_config = nullptr;
    /**
     * @fn documents core object
     */
    DocumentsCore *m_documents = nullptr;
    /**
     * @brief favorites core object
     */
    FavoritesCore *m_favorites = nullptr;
    /**
     * @brief filemanager core object
     */
    FileManagerCore *m_filemanager = nullptr;
    /**
     * @brief launcher core object
     */
    LauncherCore *m_launcher = nullptr;
    /**
     * @brief platform plugin object
     */
    DesktopInterface *m_platformPlugin = nullptr;
    /**
     * @brief plugin core object
     */
    PluginCore *m_plugin = nullptr;
    /**
     * @brief recently core object
     */
    RecentlyCore *m_recently = nullptr;
};
};


#endif /* QUADROCORE_H */
