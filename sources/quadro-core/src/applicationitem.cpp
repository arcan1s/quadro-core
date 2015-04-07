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
#include <QDir>
#include <QFileInfo>
#include <QLocale>
#include <QSettings>
#include <QStandardPaths>

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
void ApplicationItem::setCategories(const QStringList _categories)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Categories" << _categories;

    m_categories = _categories;
}


/**
 * @fn setComment
 */
void ApplicationItem::setComment(const QString _comment)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Comment" << _comment;

    m_comment = _comment;
}


/**
 * @fn setIcon
 */
void ApplicationItem::setIcon(const QIcon _icon)
{
    if (debug) qDebug() << PDEBUG;

    m_icon = _icon;
}


/**
 * @fn setIconByName
 */
void ApplicationItem::setIconByName(const QString _iconName)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Icon name" << _iconName;

    return setIcon(QIcon::fromTheme(_iconName));
}


/**
 * @fn setName
 */
void ApplicationItem::setName(const QString _name)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Name" << _name;

    m_name = _name.isEmpty() ? QFileInfo(executable()).fileName() : _name;
}


/**
 * @fn fromDesktop
 */
ApplicationItem ApplicationItem::fromDesktop(const QString _desktopPath)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Desktop path" << _desktopPath;

    QSettings settings(_desktopPath, QSettings::IniFormat);

    settings.beginGroup(QString("[Desktop Entry]"));
    QString name = settings.value(QString("Name")).toString();
    QString executable = settings.value(QString("Exec")).toString();
    QString iconPath = settings.value(QString("Icon")).toString();
    QString categories = settings.value(QString("Categories")).toString();
    // comments field
    QString locale = QLocale::system().name();
    QString localeCommentKey = QString("Comment[%1]").arg(locale.split(QChar('_'))[0]);
    QString comment = settings.contains(localeCommentKey) ?
                        settings.value(localeCommentKey).toString() :
                        settings.value(QString("Comment")).toString();
    settings.endGroup();

    ApplicationItem item = ApplicationItem::ApplicationItem(executable, name, debug);
    item.setComment(comment);
    item.setIconByName(iconPath);
    item.setCategories(categories.split(QChar(';'), QString::SkipEmptyParts));

    return item;
}


/**
 * @fn saveDesktop
 */
QString ApplicationItem::saveDesktop()
{
    if (debug) qDebug() << PDEBUG;

    QString fileName = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation);
    fileName += QDir::separator();
    fileName += name();
    QSettings settings(fileName, QSettings::IniFormat);
    if (debug) qDebug() << PDEBUG << ":" << "Configuration file" << settings.fileName();

    settings.beginGroup(QString("Desktop Entry"));
    settings.setValue(QString("Encoding"), QString("UTF-8"));
    settings.setValue(QString("Name"), name());
    settings.setValue(QString("Comment"), comment());
    settings.setValue(QString("Exec"), executable());
    settings.setValue(QString("Icon"), icon().name());
    settings.setValue(QString("Categories"), categories().join(QChar(';')));
    settings.endGroup();

    settings.sync();

    QString result = settings.status() == QSettings::NoError ? fileName : QString();
    return result;
}
