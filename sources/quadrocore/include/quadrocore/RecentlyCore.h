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
 * @file RecentlyCore.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef RECENTLYCORE_H
#define RECENTLYCORE_H

#include <QDateTime>
#include <QMap>
#include <QStringList>

#include "AbstractAppAggregator.h"


/**
 * @namespace Quadro
 */
namespace Quadro
{
/**
 * @brief The RecentlyCore class provides backend for recently run items
 */
class RecentlyCore : public AbstractAppAggregator
{
    Q_OBJECT

public:
    /**
     * @brief RecentlyCore class constructor
     * @param _parent pointer to parent item
     * @param _recentItems count of recent items in the launcher
     */
    explicit RecentlyCore(QObject *_parent, const int _recentItems);

    /**
     * @brief RecentlyCore class destructor
     */
    virtual ~RecentlyCore();

    /**
     * @brief find applications by substring in name
     * @remark override parent method to get items only if they start with
     * substring
     * @param _substr substring to which application need to be found
     * @return map of applications by substring
     */
    QMap<QString, ApplicationItem *>
    applicationsBySubstr(const QString &_substr) const;

    /**
     * @brief path to desktop files
     * @return full path to desktop files
     */
    static QString desktopPath();

    /**
     * @brief return applications which has desktop files
     * @return map of generated ApplicationItem
     */
    QMap<QString, ApplicationItem *> getApplicationsFromDesktops();

    /**
     * @brief get recently run applications
     * @return application names
     */
    QStringList recent() const;

public slots:

    /**
     * @brief add item to recent run
     * @param _item pointer to recent item run
     * @return pointer to created ApplicationItem
     */
    ApplicationItem *addItem(ApplicationItem *_item);

    /**
     * @brief add item to recent run by its name
     * @param _name recent application name
     * @return pointer to created ApplicationItem
     */
    ApplicationItem *addItem(const QString &_name);

    /**
     * @brief init application using given paths
     */
    void initApplications();

    /**
     * @brief remove item from recent run by its name
     * @param _name item name
     */
    void removeItemByName(const QString &_name);

    /**
     * @brief touch application on new run
     * @param _name name if application item
     */
    void touchItem(const QString &_name);

private:
    /**
     * @brief list of loaded applications sorted by modification times
     */
    QStringList m_modifications;
    /**
     * @brief max recent items count
     */
    int m_recentItems;

    /**
     * @brief rotate application data information
     */
    void rotate();
};
};


#endif /* RECENTLYCORE_H */
