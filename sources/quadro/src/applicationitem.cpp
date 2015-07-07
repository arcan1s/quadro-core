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
#include <QProcess>
#include <QSettings>

#include <quadro/quadro.h>
#include <pdebug/pdebug.h>


/**
 * @class ApplicationItem
 */
/**
 * @fn ApplicationItem
 */
ApplicationItem::ApplicationItem(QObject *parent, const QString exePath,
                                 const QString name, const bool debugCmd)
    : QObject(parent),
      debug(debugCmd),
      m_executable(exePath)
{
    setName(name);
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
 * @fn isHidden
 */
bool ApplicationItem::isHidden()
{
    if (debug) qDebug() << PDEBUG;

    return m_hidden;
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
 * @fn noDesktop
 */
bool ApplicationItem::noDesktop()
{
    if (debug) qDebug() << PDEBUG;

    return m_noDesktop;
}


/**
 * @fn shouldBeShown
 */
bool ApplicationItem::shouldBeShown()
{
    if (debug) qDebug() << PDEBUG;

    return (!noDesktop() && !isHidden());
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
 * @fn setHidden
 */
void ApplicationItem::setHidden(const bool _hidden)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Is hidden" << _hidden;

    m_hidden = _hidden;
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
 * @fn setNoDesktop
 */
void ApplicationItem::setNoDesktop(const bool _noDesktop)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "No desktop" << _noDesktop;

    m_noDesktop = _noDesktop;
}


/**
 * @fn fromDesktop
 */
ApplicationItem *ApplicationItem::fromDesktop(const QString _desktopPath, QObject *_parent,
                                              const bool debugCmd)
{
    QSettings settings(_desktopPath, QSettings::IniFormat);

    settings.beginGroup(QString("[Desktop Entry]"));
    QString name = settings.value(QString("Name")).toString();
    QString executable = settings.value(QString("Exec")).toString();
    QString iconPath = settings.value(QString("Icon")).toString();
    QString categories = settings.value(QString("Categories")).toString();
    bool hidden = settings.value(QString("Hidden"), QVariant(false)).toString() == QString("true");
    bool noDesktop = settings.value(QString("NoDesktop"), QVariant(false)).toString() == QString("true");
    // comments field
    QString locale = QLocale::system().name();
    QString localeCommentKey = QString("Comment[%1]").arg(locale.split(QChar('_'))[0]);
    QString comment = settings.contains(localeCommentKey) ?
                          settings.value(localeCommentKey).toString() :
                          settings.value(QString("Comment")).toString();
    settings.endGroup();

    ApplicationItem *item = new ApplicationItem(_parent, executable, name, debugCmd);
    item->setComment(comment);
    item->setHidden(hidden);
    item->setIconByName(iconPath);
    item->setNoDesktop(noDesktop);
    item->setCategories(categories.split(QChar(';'), QString::SkipEmptyParts));

    return item;
}


/**
 * @fn launch
 */
bool ApplicationItem::launch()
{
    if (debug) qDebug() << PDEBUG;

    return QProcess::startDetached(executable());
}


/**
 * @fn saveDesktop
 */
QString ApplicationItem::saveDesktop(const QString _desktopPath)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Desktop path" << _desktopPath;

    QString fileName = QString("%1/%2.desktop").arg(_desktopPath).arg(name());
    QSettings settings(fileName, QSettings::IniFormat);
    if (debug) qDebug() << PDEBUG << ":" << "Configuration file" << settings.fileName();

    settings.beginGroup(QString("Desktop Entry"));
    settings.setValue(QString("Encoding"), QString("UTF-8"));
    settings.setValue(QString("Name"), name());
    settings.setValue(QString("Comment"), comment());
    settings.setValue(QString("Exec"), executable());
    settings.setValue(QString("Icon"), icon().name());
    settings.setValue(QString("Categories"), categories().join(QChar(';')));
    settings.setValue(QString("Hidden"), QVariant(isHidden()).toString());
    settings.setValue(QString("NoDesktop"), QVariant(noDesktop()).toString());
    settings.endGroup();

    settings.sync();

    QString result = settings.status() == QSettings::NoError ? fileName : QString();
    return result;
}
