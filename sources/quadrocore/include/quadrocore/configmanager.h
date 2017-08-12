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
 * @file configmanager.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>
#include <QVariant>


/**
 * @brief the ConfigManager provides common operations with Quadro configuration
 */
class ConfigManager : public QObject
{
    Q_OBJECT
    // core
    Q_PROPERTY(QString path READ path)
    // configuration
    Q_PROPERTY(int GridSize READ gridSize)
    Q_PROPERTY(int RecentItemsCount READ recentItemCount)

public:
    /**
     * @brief ConfigManager class constructor
     * @param _parent pointer to parent object
     */
    explicit ConfigManager(QObject *_parent);
    /**
     * @brief ConfigManager class destructor
     */
    virtual ~ConfigManager();
    /**
     * @brief set settings from other source
     * @remark to use this method please make sure that you've asked
     * ConfigManager::verifySettings are settings valid or not
     * @param _other other settings dictionary
     * @return true if settings have been applied successfully. Otherwise
     * returns false
     */
    bool setSettings(const QVariantHash &_other);
    /**
     * @brief verify settings from other source
     * @param _other other settings dictionary
     * @param _ok if this parameter is given it will contain the verification
     * status
     * @returns keys in which there are invalid values. If no errors were found
     * it will be empty list
     */
    static QStringList verifySettings(const QVariantHash &_other,
                                      bool *_ok = nullptr);
    // core properties
    /**
     * @brief get path to configuration file
     * @return full path to applied configuration file
     */
    QString path() const;
    // configuration properties
    /**
     * @brief UI item grid size
     * @return grid size in pixels
     */
    int gridSize() const;
    /**
     * @brief maximum recently run application count to store
     * @return maximum count
     */
    int recentItemCount() const;

public slots:
    /**
     * @brief read settings from file
     * @param _defaults if it is set to true default settings will be read
     */
    void readSettings(const bool _defaults = false);
    /**
     * @brief current settings to file
     * @return true if settings have been saved successfully
     */
    bool saveSettings() const;

private:
    // properties
    /**
     * @brief path to configuration file
     */
    QString m_path;
    /**
     * @brief configuration dictionary
     */
    QVariantHash m_configuration;
};


#endif /* CONFIGMANAGER_H */
