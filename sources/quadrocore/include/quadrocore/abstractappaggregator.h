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
 * @file abstractappaggregator.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef ABSTRACTAPPAGGREGATOR_H
#define ABSTRACTAPPAGGREGATOR_H

// QMap class required because applications should be sorted
#include <QMap>
#include <QObject>


class ApplicationItem;

/**
 * @brief The AbstractAppAggregator class provides application aggregator
 * backend
 */
class AbstractAppAggregator : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief AbstractAppAggregator class constructor
     * @param parent         pointer to parent item
     */
    explicit AbstractAppAggregator(QObject *parent);
    /**
     * @brief AbstractAppAggregator class destructor
     */
    virtual ~AbstractAppAggregator();
    /**
     * @brief find applications
     * @return map of applications
     */
    QMap<QString, ApplicationItem *> applications() const;
    /**
     * @brief find applications by category
     * @param _category      category
     * @return map of applications by category
     */
    QMap<QString, ApplicationItem *>
    applicationsByCategory(const QString _category) const;
    /**
     * @brief find applications by substring in name
     * @param _substr        substring to which application need to be found
     * @return map of applications by substring
     */
    QMap<QString, ApplicationItem *>
    applicationsBySubstr(const QString _substr) const;
    /**
     * @brief available application categories
     * @return list of available categories
     */
    static QStringList availableCategories();
    /**
     * @brief is application has been read
     * @param _name          application name
     * @return true if application has been found
     * @return false if the application has not been found
     */
    bool hasApplication(const QString _name) const;

public slots:
    /**
     * @brief add application to array
     * @param _item          application item
     */
    void addApplication(ApplicationItem *_item);
    /**
     * @brief clear application array
     */
    void dropApplications();
    /**
     * @brief init application using given paths
     */
    virtual void initApplications() = 0;
    /**
     * @brief remove application from array
     * @param _item          application item
     */
    void removeApplication(ApplicationItem *_item);

private:
    /**
     * @brief list of applications
     */
    QMap<QString, ApplicationItem *> m_applications;
    /**
     * @brief return applications which has desktop files
     * @return map of generated ApplicationItem
     */
    virtual QMap<QString, ApplicationItem *> getApplicationsFromDesktops() = 0;
};


#endif /* ABSTRACTAPPAGGREGATOR_H */
