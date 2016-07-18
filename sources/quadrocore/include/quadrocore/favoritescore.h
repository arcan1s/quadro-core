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
 * @file favoritescore.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef FAVORITECORE_H
#define FAVORITECORE_H

#include <QMap>
#include <QObject>


class ApplicationItem;

/**
 * @brief The FavoritesCore class provides favorites backend
 */
class FavoritesCore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString desktopPath READ desktopPath)

public:
    /**
     * @brief FavoritesCore class constructor
     * @param parent         pointer to parent item
     */
    explicit FavoritesCore(QObject *parent);
    /**
     * @brief FavoritesCore class destructor
     */
    virtual ~FavoritesCore();
    /**
     * @brief add or remove application to the favorites items
     * @param _item          pointer to application item object
     */
    void add(ApplicationItem *_item);
    /**
     * @brief find applications
     * @return map of applications
     */
    QMap<QString, ApplicationItem *> applications() const;
    /**
     * @brief add or remove application to the favorites items
     * @param _item          pointer to application item object
     * @return application item
     */
    static ApplicationItem *addToFavorites(ApplicationItem *_item);
    /**
     * @brief add or remove application to the favorites items
     * @param _executable    path to executable
     * @param _name          desktop name
     * @param _iconName      icon name in the theme
     * @return application item
     */
    static ApplicationItem *
    addToFavorites(const QString _executable, const QString _name = QString(),
                   const QString _iconName = QString("system-run"));
    /**
     * @brief check whether the application in favorites
     * @param _item          pointer to application item object
     * @return true if application is in favorites otherwise returns false
     */
    bool check(ApplicationItem *_item);
    /**
     * @brief path to desktop files
     * @return full path to desktop files
     */
    static QString desktopPath();
    /**
     * @brief check whether the application in favorites
     * @param _item          pointer to application item object
     * @return true if application is in favorites otherwise returns false
     */
    static bool hasApplication(ApplicationItem *_item);
    /**
     * @brief application order
     * @return list of applications by name
     */
    QStringList order() const;

public slots:
    /**
     * @brief move given application up or down
     * @param _name          desktop name
     * @param _up            move application up, default is true
     */
    void changeApplicationState(const QString _name, const bool _up = true);
    /**
     * @brief init application from default paths
     */
    void initApplications();
    /**
     * @brief save current application order to the index file
     */
    void saveApplicationsOrder() const;

private:
    /**
     * @brief list of applications
     */
    QMap<QString, ApplicationItem *> m_applications;
    /**
     * @brief order of applications
     */
    QStringList m_order;
    /**
     * @brief add application to favorites
     * @param _item          pointer to application item
     */
    void addAppToFavorites(ApplicationItem *_item);
    /**
     * @brief return applications which has desktop files
     * @return map of generated ApplicationItem
     */
    QMap<QString, ApplicationItem *> getApplicationsFromDesktops();
    /**
     * @brief return correct applications order
     * @return list of applications in the correct order
     */
    QStringList getApplicationsOrder() const;
    /**
     * @brief remove application from favorites
     * @param _item          pointer to application item
     */
    void removeAppFromFavorites(ApplicationItem *_item);
};


#endif /* FAVORITECORE_H */
