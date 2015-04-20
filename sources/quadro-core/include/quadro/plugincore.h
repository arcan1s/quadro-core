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
 * @file plugincore.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef PLUGINCORE_H
#define PLUGINCORE_H

#include <QMap>
#include <QObject>
#include <QStringList>


class PluginItem;

/**
 * @brief The PluginCore class provides plugin backend
 */
class PluginCore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList desktopPaths READ desktopPaths)

public:
    /**
     * @brief PluginCore class constructor
     * @param parent         pointer to parent item
     * @param debugCmd       show debug messages
     */
    explicit PluginCore(QObject *parent, const bool debugCmd = false);
    /**
     * @brief PluginCore class destructor
     */
    ~PluginCore();
    /**
     * @brief get list of enabled plugins
     * @return list of active plugins
     */
    QStringList activePlugins();
    /**
     * @brief path to plugin desktop files
     * @return full paths to plugin desktop files
     */
    static QStringList desktopPaths();
    /**
     * @brief find plugins
     * @return map of plugins
     */
    QMap<QString, PluginItem *> plugins();

public slots:
    /**
     * @brief init plugins from default paths
     */
    void initPlugins();
    /**
     * @brief run specified plugins
     * @param _plugins       names of desktop files of plugins which should be run
     */
    void runPlugins(const QStringList _plugins);
    /**
     * @brief save given plugins to the index file
     * @param _plugins       names of desktop files of plugins which should be saved
     */
    void saveActivePlugins(const QStringList _plugins);

private:
    /**
     * @brief show debug messages. Default is false
     */
    bool debug = false;
    /**
     * @brief list of plugins
     */
    QMap<QString, PluginItem *> m_plugins;
    /**
     * @brief list of plugin libraries
     */
    QMap<QString, void *> m_pluginsLibs;
    /**
     * @brief return plugins from default paths
     * @return map of generated PluginItem
     */
    QMap<QString, PluginItem *> getPlugins();
};


#endif /* PLUGINCORE_H */
