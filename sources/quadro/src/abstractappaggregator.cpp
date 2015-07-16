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


#include <QDebug>
#include <QDir>
#include <QProcessEnvironment>
#include <QStandardPaths>

#include <quadro/quadro.h>
#include <pdebug/pdebug.h>


/**
 * @class AbstractAppAggregator
 */
/**
 * @fn AbstractAppAggregator
 */
AbstractAppAggregator::AbstractAppAggregator(QObject *parent, const bool debugCmd)
    : QObject(parent),
      debug(debugCmd)
{
}


/**
 * @fn ~AbstractAppAggregator
 */
AbstractAppAggregator::~AbstractAppAggregator()
{
    if (debug) qDebug() << PDEBUG;

    dropApplications();
}


/**
 * @fn applications
 */
QMap<QString, ApplicationItem *> AbstractAppAggregator::applications() const
{
    if (debug) qDebug() << PDEBUG;

    return m_applications;
}


/**
 * @fn applicationsByCategory
 */
QMap<QString, ApplicationItem *> AbstractAppAggregator::applicationsByCategory(const QString _category) const
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Category" << _category;

    QMap<QString, ApplicationItem *> apps;
    if (!availableCategories().contains(_category)) {
        if (debug) qDebug() << PDEBUG << ":" << "Incorrect category" << _category;
        return apps;
    }

    for (int i=0; i<m_applications.keys().count(); i++) {
        QString key = m_applications.keys()[i];
        QStringList categories = m_applications[key]->categories();
        if (!categories.contains(_category)) continue;
        apps[key] = m_applications[key];
    }

    return apps;
}


/**
 * @fn applicationsBySubstr
 */
QMap<QString, ApplicationItem *> AbstractAppAggregator::applicationsBySubstr(const QString _substr) const
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Substring" << _substr;

    QMap<QString, ApplicationItem *> apps;
    // from desktops
    for (int i=0; i<m_applications.keys().count(); i++) {
        QString key = m_applications.keys()[i];
        if (!m_applications[key]->hasSubstring(_substr)) continue;
        apps[key] = m_applications[key];
    }

    return apps;
}


/**
 * @fn availableCategories
 */
QStringList AbstractAppAggregator::availableCategories() const
{
    if (debug) qDebug() << PDEBUG;
    // refer to http://standards.freedesktop.org/menu-spec/latest/apa.html

    QStringList categories;
    categories.append(QString("AudioVideo"));       // usually named as Multimedia
    categories.append(QString("Audio"));
    categories.append(QString("Video"));
    categories.append(QString("Development"));
    categories.append(QString("Education"));
    categories.append(QString("Game"));
    categories.append(QString("Graphics"));
    categories.append(QString("Network"));
    categories.append(QString("Office"));
    categories.append(QString("Science"));
    categories.append(QString("Settings"));
    categories.append(QString("System"));
    categories.append(QString("Utility"));

    if (debug) qDebug() << PDEBUG << ":" << "Found categories" << categories;
    return categories;
}


/**
 * @fn hasApplication
 */
bool AbstractAppAggregator::hasApplication(const QString _name) const
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Application name" << _name;

    return m_applications.contains(_name);
}


/**
 * @fn addApplication
 */
void AbstractAppAggregator::addApplication(ApplicationItem *_item)
{
    if (debug) qDebug() << PDEBUG;

    m_applications[_item->name()] = _item;
}


/**
 * @fn dropApplications
 */
void AbstractAppAggregator::dropApplications()
{
    if (debug) qDebug() << PDEBUG;

    m_applications.clear();
}
