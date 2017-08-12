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
 * @file abstractappaggregator.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadrocore/quadro.h"


/**
 * @class AbstractAppAggregator
 */
/**
 * @fn AbstractAppAggregator
 */
AbstractAppAggregator::AbstractAppAggregator(QObject *_parent)
    : QObject(_parent)
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;
}


/**
 * @fn ~AbstractAppAggregator
 */
AbstractAppAggregator::~AbstractAppAggregator()
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;

    dropApplications();
}


/**
 * @fn applications
 */
QMap<QString, ApplicationItem *> AbstractAppAggregator::applications() const
{
    return m_applications;
}


/**
 * @fn applicationsByCategory
 */
QMap<QString, ApplicationItem *>
AbstractAppAggregator::applicationsByCategory(const QString &_category) const
{
    qCDebug(LOG_LIB) << "Category" << _category;

    QMap<QString, ApplicationItem *> apps;
    if (!availableCategories().contains(_category)) {
        qCCritical(LOG_LIB) << "Incorrect category" << _category;
        return apps;
    }

    for (auto &app : m_applications.keys()) {
        QStringList categories = m_applications[app]->categories();
        if (!categories.contains(_category))
            continue;
        apps[app] = m_applications[app];
    }

    return apps;
}


/**
 * @fn applicationsBySubstr
 */
QMap<QString, ApplicationItem *>
AbstractAppAggregator::applicationsBySubstr(const QString &_substr) const
{
    qCDebug(LOG_LIB) << "Substring" << _substr;

    QMap<QString, ApplicationItem *> apps;
    for (auto &app : m_applications.keys()) {
        if (!m_applications[app]->hasSubstring(_substr))
            continue;
        apps[app] = m_applications[app];
    }

    return apps;
}


/**
 * @fn availableCategories
 */
QStringList AbstractAppAggregator::availableCategories()
{
    // refer to http://standards.freedesktop.org/menu-spec/latest/apa.html

    QStringList categories;
    categories.append("AudioVideo"); // usually named as Multimedia
    categories.append("Audio");
    categories.append("Video");
    categories.append("Development");
    categories.append("Education");
    categories.append("Game");
    categories.append("Graphics");
    categories.append("Network");
    categories.append("Office");
    categories.append("Science");
    categories.append("Settings");
    categories.append("System");
    categories.append("Utility");

    qCInfo(LOG_LIB) << "Found categories" << categories;
    return categories;
}


/**
 * @fn hasApplication
 */
bool AbstractAppAggregator::hasApplication(const QString &_name) const
{
    qCDebug(LOG_LIB) << "Application name" << _name;

    return m_applications.contains(_name);
}


/**
 * @fn addApplication
 */
void AbstractAppAggregator::addApplication(ApplicationItem *_item)
{
    m_applications[_item->name()] = _item;
}


/**
 * @fn dropApplications
 */
void AbstractAppAggregator::dropApplications()
{
    m_applications.clear();
}


/**
 * @fn removeApplication
 */
void AbstractAppAggregator::removeApplication(ApplicationItem *_item)
{
    QStringList keys = m_applications.keys(_item);

    for (auto &app : keys)
        m_applications.remove(app);
}
