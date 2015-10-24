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


#include "quadro/quadro.h"

#include <QDir>
#include <QFileInfo>
#include <QLocale>
#include <QProcess>
#include <QSettings>


/**
 * @class ApplicationItem
 */
/**
 * @fn ApplicationItem
 */
ApplicationItem::ApplicationItem(QObject *parent, const QString exePath,
                                 const QString name)
    : QObject(parent),
      m_executable(exePath)
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;

    setName(name);
}


/**
 * @fn ~ApplicationItem
 */
ApplicationItem::~ApplicationItem()
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;
}


/**
 * @fn categories
 */
QStringList ApplicationItem::categories() const
{
    return m_categories;
}


/**
 * @fn comment
 */
QString ApplicationItem::comment() const
{
    return m_comment;
}


/**
 * @fn desktopName
 */
QString ApplicationItem::desktopName() const
{
    return m_desktopName.isEmpty() ? QString("%1.desktop").arg(m_name) : m_desktopName;
}


/**
 * @fn executable
 */
QString ApplicationItem::executable() const
{
    return m_executable;
}


/**
 * @fn hasSubstring
 */
bool ApplicationItem::hasSubstring(const QString _substr) const
{
    return ((m_name.contains(_substr, Qt::CaseInsensitive)) ||
            (m_comment.contains(_substr, Qt::CaseInsensitive)));
}


/**
 * @fn isHidden
 */
bool ApplicationItem::isHidden() const
{
    return m_hidden;
}


/**
 * @fn icon
 */
QIcon ApplicationItem::icon() const
{
    return m_icon;
}


/**
 * @fn name
 */
QString ApplicationItem::name() const
{
    return m_name;
}


/**
 * @fn noDesktop
 */
bool ApplicationItem::noDesktop() const
{
    return m_noDesktop;
}


/**
 * @fn shouldBeShown
 */
bool ApplicationItem::shouldBeShown() const
{
    return (!m_noDesktop && !m_hidden);
}


/**
 * @fn startsWith
 */
bool ApplicationItem::startsWith(const QString _substr) const
{
    return m_executable.startsWith(_substr);
}


/**
 * @fn setCategories
 */
void ApplicationItem::setCategories(const QStringList _categories)
{
    qCDebug(LOG_LIB) << "Categories" << _categories;

    m_categories = _categories;
}


/**
 * @fn setComment
 */
void ApplicationItem::setComment(const QString _comment)
{
    qCDebug(LOG_LIB) << "Comment" << _comment;

    m_comment = _comment;
}


/**
 * @fn setDesktopName
 */
void ApplicationItem::setDesktopName(const QString _desktopName)
{
    qCDebug(LOG_LIB) << "Desktop name" << _desktopName;

    m_desktopName = _desktopName;
}


/**
 * @fn setHidden
 */
void ApplicationItem::setHidden(const bool _hidden)
{
    qCDebug(LOG_LIB) << "Is hidden" << _hidden;

    m_hidden = _hidden;
}


/**
 * @fn setIcon
 */
void ApplicationItem::setIcon(const QIcon _icon)
{
    m_icon = _icon;
}


/**
 * @fn setIconByName
 */
void ApplicationItem::setIconByName(const QString _iconName)
{
    qCDebug(LOG_LIB) << "Icon name" << _iconName;

    return setIcon(QIcon::fromTheme(_iconName));
}


/**
 * @fn setName
 */
void ApplicationItem::setName(const QString _name)
{
    qCDebug(LOG_LIB) << "Name" << _name;

    m_name = _name.isEmpty() ? QFileInfo(executable()).fileName() : _name;
}


/**
 * @fn setNoDesktop
 */
void ApplicationItem::setNoDesktop(const bool _noDesktop)
{
    qCDebug(LOG_LIB) << "No desktop" << _noDesktop;

    m_noDesktop = _noDesktop;
}


/**
 * @fn fromDesktop
 */
ApplicationItem *ApplicationItem::fromDesktop(const QString _desktopPath, QObject *_parent)
{
    qCDebug(LOG_LIB) << "Desktop path" << _desktopPath;
    QSettings settings(_desktopPath, QSettings::IniFormat);

    settings.beginGroup(QString("Desktop Entry"));
    QString name = settings.value(QString("Name")).toString();
    QString executable = settings.value(QString("Exec")).toString();
    QString iconPath = settings.value(QString("Icon")).toString();
    bool hidden = settings.value(QString("Hidden"), QVariant(false)).toString() == QString("true");
    bool noDesktop = settings.value(QString("NoDesktop"), QVariant(false)).toString() == QString("true");
    // comments field
    QString locale = QLocale::system().name();
    QString localeCommentKey = QString("Comment[%1]").arg(locale.split(QChar('_'))[0]);
    QString comment = settings.contains(localeCommentKey) ?
                          settings.value(localeCommentKey).toString() :
                          settings.value(QString("Comment")).toString();
    settings.endGroup();

    ApplicationItem *item = new ApplicationItem(_parent, executable, name);
    item->setComment(comment);
    item->setHidden(hidden);
    item->setIconByName(iconPath);
    item->setNoDesktop(noDesktop);
    item->defineCategories(_desktopPath);
    item->setDesktopName(QFileInfo(_desktopPath).fileName());

    return item;
}


/**
 * @fn defineCategories
 */
void ApplicationItem::defineCategories(const QString _desktopPath)
{
    qCDebug(LOG_LIB) << "Desktop path" << _desktopPath;

    // open
    QFile desktopFile(_desktopPath);
    if (!desktopFile.open(QIODevice::ReadOnly))
        return setCategories();
    // parse
    QStringList foundCategories;
    while (true) {
        QString fileStr = QString(desktopFile.readLine()).trimmed();
        if (fileStr.startsWith(QString("Categories"))) {
            // hope category name will not contain '='
            foundCategories = fileStr.split(QChar('='))[1].split(QChar(';'), QString::SkipEmptyParts);
            break;
        }
        if (desktopFile.atEnd()) break;
    }
    // close
    desktopFile.close();

    return setCategories(foundCategories);
}


/**
 * @fn launch
 */
bool ApplicationItem::launch() const
{
    // FIXME workaround to allow launch items with parameters
    QStringList args = executable().split(QChar(' ')).filter(QRegExp(QString("^(?!%).*")));
    QString cmd = args.takeAt(0);

    return QProcess::startDetached(cmd, args);
}


/**
 * @fn saveDesktop
 */
QString ApplicationItem::saveDesktop(const QString _desktopPath) const
{
    qCDebug(LOG_LIB) << "Desktop path" << _desktopPath;

    QString fileName = QString("%1/%2").arg(_desktopPath).arg(desktopName());
    QSettings settings(fileName, QSettings::IniFormat);
    qCInfo(LOG_LIB) << "Configuration file" << settings.fileName();

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
