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
 * @file applicationitem.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include <QDebug>

#include <quadro/quadro.h>
#include <pdebug/pdebug.h>


/**
 * @class ApplicationItem
 */
/**
 * @fn ApplicationItem
 */
ApplicationItem::ApplicationItem(const QString exePath, const QString name,
                                 const bool debugCmd)
    : debug(debugCmd),
      m_executable(exePath)
{
}


/**
 * @fn ~ApplicationItem
 */
ApplicationItem::~ApplicationItem()
{
    if (debug) qDebug() << PDEBUG;
}


/**
 * @fn categories
 */
QStringList ApplicationItem::categories()
{
    if (debug) qDebug() << PDEBUG;

    return m_categories;
}


/**
 * @fn comment
 */
QString ApplicationItem::comment()
{
    if (debug) qDebug() << PDEBUG;

    return m_comment;
}


/**
 * @fn executable
 */
QString ApplicationItem::executable()
{
    if (debug) qDebug() << PDEBUG;

    return m_executable;
}


/**
 * @fn icon
 */
QIcon ApplicationItem::icon()
{
    if (debug) qDebug() << PDEBUG;

    return m_icon;
}


/**
 * @fn name
 */
QString ApplicationItem::name()
{
    if (debug) qDebug() << PDEBUG;

    return m_name;
}


/**
 * @fn setCategories
 */
void ApplicationItem::setCategories(QStringList _categories)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Categories" << _categories;

    m_categories = _categories;
}


/**
 * @fn setComment
 */
void ApplicationItem::setComment(QString _comment)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Comment" << _comment;

    m_comment = _comment;
}


/**
 * @fn setIcon
 */
void ApplicationItem::setIcon(QIcon _icon)
{
    if (debug) qDebug() << PDEBUG;

    m_icon = _icon;
}


/**
 * @fn setIconByName
 */
void ApplicationItem::setIconByName(QString _iconName)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Icon name" << _iconName;

    return setIcon(QIcon::fromTheme(_iconName));
}


/**
 * @fn setName
 */
void ApplicationItem::setName(QString _name)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Name" << _name;

    m_name = _name.isEmpty() ? executable() : _name;
}
