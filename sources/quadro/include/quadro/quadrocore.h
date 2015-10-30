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
 * @file quadrocore.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef QUADROCORE_H
#define QUADROCORE_H

#include <QObject>
#include "recentlycore.h"


class FavoritesCore;
class FileManagerCore;
class LauncherCore;
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
     * @param parent         pointer to parent item
     * @param configuration  setting map
     */
    explicit QuadroCore(QObject *parent, const QVariantHash configuration);
    /**
     * @brief QuadroCore class destructor
     */
    virtual ~QuadroCore();
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
     * @brief recently core object
     */
    RecentlyCore *m_recently = nullptr;
    /**
     * @brief configuration
     */
    QVariantHash m_configuration;
};


#endif /* QUADROCORE_H */
