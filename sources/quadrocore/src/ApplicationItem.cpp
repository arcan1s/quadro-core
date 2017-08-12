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
 * @file ApplicationItem.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadrocore/Quadro.h"

#include <QDesktopServices>
#include <QDir>
#include <QFileInfo>
#include <QIcon>
#include <QLocale>
#include <QProcess>
#include <QSettings>
#include <QUrl>

using namespace Quadro;


/**
 * @class ApplicationItem
 */
/**
 * @fn ApplicationItem
 */
ApplicationItem::ApplicationItem(QObject *_parent, const QString &_name)
    : QObject(_parent)
    , m_name(_name)
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;
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
 * @fn exec
 */
QString ApplicationItem::exec() const
{
    return m_exec;
}


/**
 * @fn genericName
 */
QString ApplicationItem::genericName() const
{
    return m_genericName;
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
QString ApplicationItem::icon() const
{
    return m_icon;
}


/**
 * @fn keywords
 */
QStringList ApplicationItem::keywords() const
{
    return m_keywords;
}


/**
 * @fn mimeType
 */
QStringList ApplicationItem::mimeType() const
{
    return m_mimeType;
}


/**
 * @fn name
 */
QString ApplicationItem::name() const
{
    return m_name;
}


/**
 * @fn noDisplay
 */
bool ApplicationItem::noDisplay() const
{
    return m_noDisplay;
}


/**
 * @fn path
 */
QString ApplicationItem::path() const
{
    return m_path;
}


/**
 * @fn url
 */
QString ApplicationItem::url() const
{
    return m_url;
}


/**
 * @fn terminal
 */
bool ApplicationItem::terminal() const
{
    return m_terminal;
}


/**
 * @fn tryExec
 */
QString ApplicationItem::tryExec() const
{
    return m_tryExec;
}


/**
 * @fn type
 */
QString ApplicationItem::type() const
{
    return m_type;
}


/**
 * @fn version
 */
QString ApplicationItem::version() const
{
    return m_version;
}


/**
 * @fn setCategories
 */
void ApplicationItem::setCategories(const QStringList &_categories)
{
    qCDebug(LOG_LIB) << "Categories" << _categories;

    m_categories = _categories;
}


/**
 * @fn setComment
 */
void ApplicationItem::setComment(const QString &_comment)
{
    qCDebug(LOG_LIB) << "Comment" << _comment;

    m_comment = _comment;
}


/**
 * @fn setExec
 */
void ApplicationItem::setExec(const QString &_exec)
{
    qCDebug(LOG_LIB) << "Executable" << _exec;

    m_exec = _exec;
}


/**
 * @fn setGenericName
 */
void ApplicationItem::setGenericName(const QString &_genericName)
{
    qCDebug(LOG_LIB) << "Generic name" << _genericName;

    m_genericName = _genericName;
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
 * @fn setIconByName
 */
void ApplicationItem::setIcon(const QString &_icon)
{
    qCDebug(LOG_LIB) << "Icon name" << _icon;

    m_icon = _icon;
}


/**
 * @fn setKeywords
 */
void ApplicationItem::setKeywords(const QStringList &_keywords)
{
    qCDebug(LOG_LIB) << "Application keywords" << _keywords;

    m_keywords = _keywords;
}


/**
 * @fn setMimeType
 */
void ApplicationItem::setMimeType(const QStringList &_mimeType)
{
    qCDebug(LOG_LIB) << "MIME types" << _mimeType;

    m_mimeType = _mimeType;
}


/**
 * @fn setName
 */
void ApplicationItem::setName(const QString &_name)
{
    qCDebug(LOG_LIB) << "Name" << _name;

    m_name = _name.isEmpty() ? QFileInfo(m_exec).fileName() : _name;
}


/**
 * @fn setNoDisplay
 */
void ApplicationItem::setNoDisplay(const bool _noDisplay)
{
    qCDebug(LOG_LIB) << "No display" << _noDisplay;

    m_noDisplay = _noDisplay;
}


/**
 * @fn setPath
 */
void ApplicationItem::setPath(const QString &_path)
{
    qCDebug(LOG_LIB) << "Working directory" << _path;

    m_path = _path;
}


/**
 * @fn setUrl
 */
void ApplicationItem::setUrl(const QString &_url)
{
    qCDebug(LOG_LIB) << "URL" << _url;

    m_url = _url;
}


/**
 * @fn setTerminal
 */
void ApplicationItem::setTerminal(const bool _terminal)
{
    qCDebug(LOG_LIB) << "Use terminal" << _terminal;

    m_terminal = _terminal;
}


/**
 * @fn setTryExec
 */
void ApplicationItem::setTryExec(const QString &_tryExec)
{
    qCDebug(LOG_LIB) << "Test executable" << _tryExec;

    m_tryExec = _tryExec;
}


/**
 * @fn setType
 */
void ApplicationItem::setType(const QString &_type)
{
    qCDebug(LOG_LIB) << "Type" << _type;
    if ((_type != "Application") && (_type != "Link")
        && (_type != "Directory")) {
        qCWarning(LOG_LIB) << "Invalid desktop entry type" << _type;
        return;
    }

    m_type = _type;
}


/**
 * @fn setVersion
 */
void ApplicationItem::setVersion(const QString &_version)
{
    qCDebug(LOG_LIB) << "Version" << _version;

    m_version = _version;
}


/**
 * @fn appIcon
 */
QIcon ApplicationItem::appIcon() const
{
    return QIcon::fromTheme(m_icon);
}


/**
 * @fn defineList
 */
QStringList ApplicationItem::defineList(const QString &_desktopPath,
                                        const QString &_key)
{
    qCDebug(LOG_LIB) << "Desktop path" << _desktopPath;
    qCDebug(LOG_LIB) << "Options key" << _key;

    QStringList values;
    // open
    QFile desktopFile(_desktopPath);
    if (!desktopFile.open(QIODevice::ReadOnly))
        return values;
    // parse
    while (true) {
        QString fileStr = QString(desktopFile.readLine()).trimmed();
        if (fileStr.startsWith(QString("%1=").arg(_key))) {
            // workaround for "
            QString substr = fileStr.split('=')[1];
            substr.remove("\"");
            values = substr.split(';', QString::SkipEmptyParts);
            break;
        }
        if (desktopFile.atEnd())
            break;
    }
    // close
    desktopFile.close();

    qCInfo(LOG_LIB) << "Found values" << values << "for" << _key;
    return values;
}


/**
 * @fn desktopName
 */
QString ApplicationItem::desktopName() const
{
    return m_desktopName.isEmpty() ? QString("%1.desktop").arg(m_name)
                                   : m_desktopName;
}


/**
 * @fn generateExec
 */
QStringList ApplicationItem::generateExec(const QVariantHash &_args) const
{
    qCDebug(LOG_LIB) << "Program arguments" << _args;

    QStringList cmdArgs = m_exec.split(' ', QString::SkipEmptyParts);
    // replace keys according to
    // http://standards.freedesktop.org/desktop-entry-spec/latest/ar01s06.html
    QStringList keys = {"%f", "%F", "%u", "%U", "%d", "%D", "%n",
                        "%N", "%i", "%c", "%k", "%V", "%m"};
    for (auto &arg : cmdArgs) {
        for (auto &key : keys) {
            arg.replace(key,
                        _args[key].type() == QVariant::StringList
                            ? _args[key].toStringList().join(' ')
                            : _args[key].toString());
        }
        arg.replace("%%", "%");
    }

    // prepend $TERM if any
    if (m_terminal) {
        QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
        QString term = env.value("TERM");
        if (term.isEmpty())
            qCWarning(LOG_LIB) << "Could not get $TERM variable, ignoring";
        else
            cmdArgs.prepend(term);
    }

    return cmdArgs;
}


/**
 * @fn fromDesktop
 */
ApplicationItem *ApplicationItem::fromDesktop(const QString &_desktopPath,
                                              QObject *_parent)
{
    qCDebug(LOG_LIB) << "Desktop path" << _desktopPath;

    QSettings settings(_desktopPath, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");

    ApplicationItem *item = new ApplicationItem(_parent, "");
    settings.beginGroup("Desktop Entry");
    for (auto &key : settings.childKeys()) {
        // HACK avoid URL[$e] values in KDE
        if (key.startsWith("URL[$e]"))
            key = "URL";
        // HACK avoid commas in fields
        QVariant orig = settings.value(key);
        QVariant value = orig.type() == QVariant::StringList
                             ? orig.toStringList().join(", ")
                             : orig;
        item->setProperty(key.toUtf8().constData(), value);
    }

    // update localized fields
    // locale keys, modifier (@mod) is ignored
    QStringList locales
        = {QLocale::system().bcp47Name(), QLocale::system().name()};
    // properties which may be localised
    QStringList props = {"Name", "GenericName", "Icon", "Comment"};
    for (auto &prop : props) {
        for (auto &loc : locales) {
            QString propName = QString("%1[%2]").arg(prop).arg(loc);
            if (!settings.contains(propName))
                continue;
            // HACK avoid commas in fields
            QVariant orig = settings.value(propName);
            QVariant value = orig.type() == QVariant::StringList
                                 ? orig.toStringList().join(", ")
                                 : orig;
            item->setProperty(prop.toUtf8().constData(), value);
            break;
        }
    }

    // workaround for lists
    props = QStringList({"Categories", "Keywords", "MimeTypes"});
    for (auto &prop : props) {
        QStringList values;
        /// try localized keys
        for (auto &loc : locales) {
            QString propName = QString("%1[%2]").arg(prop).arg(loc);
            if (!settings.contains(propName))
                continue;
            values = ApplicationItem::defineList(_desktopPath, propName);
            break;
        }
        // try generic locale
        if (values.isEmpty())
            values = ApplicationItem::defineList(_desktopPath, prop);
        // set data
        item->setProperty(prop.toUtf8().constData(), values);
    }

    settings.endGroup();
    item->setDesktopName(_desktopPath);

    return item;
}


/**
 * @fn hasSubstring
 */
bool ApplicationItem::hasSubstring(const QString &_substr) const
{
    return ((m_name.contains(_substr, Qt::CaseInsensitive))
            || (m_genericName.contains(_substr, Qt::CaseInsensitive))
            || (m_comment.contains(_substr, Qt::CaseInsensitive))
            || (m_keywords.contains(_substr, Qt::CaseInsensitive)));
}


/**
 * @fn setDesktopName
 */
void ApplicationItem::setDesktopName(const QString &_desktopName)
{
    qCDebug(LOG_LIB) << "Desktop name" << _desktopName;

    m_desktopName = QFileInfo(_desktopName).fileName();
}


/**
 * @fn shouldBeShown
 */
bool ApplicationItem::shouldBeShown() const
{
    return (!m_noDisplay && !m_hidden);
}


/**
 * @fn startsWith
 */
bool ApplicationItem::startsWith(const QString &_substr) const
{
    return m_exec.startsWith(_substr);
}


/**
 * @fn launch
 */
bool ApplicationItem::launch(const QVariantHash &_args) const
{
    qCDebug(LOG_LIB) << "Program arguments" << _args;

    if (m_type == "Application") {
        if ((m_tryExec.isEmpty())
            || (!QStandardPaths::findExecutable(m_tryExec).isEmpty())) {
            return run(_args);
        } else {
            qCWarning(LOG_LIB) << "Ignore launch";
        }
    } else if (m_type == "Link") {
        return QDesktopServices::openUrl(QUrl(m_url));
    } else if (m_type == "Directory") {
        return QDesktopServices::openUrl(
            QUrl(QString("file://%1").arg(m_path)));
    }

    return false;
}


/**
 * @fn saveDesktop
 */
QString ApplicationItem::saveDesktop(const QString &_desktopPath) const
{
    qCDebug(LOG_LIB) << "Desktop path" << _desktopPath;

    QString fileName = QString("%1/%2").arg(_desktopPath).arg(desktopName());
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    qCInfo(LOG_LIB) << "Configuration file" << settings.fileName();

    // generate list of known properties
    QStringList knownProperties
        = {"Type",    "Version",  "Name",   "GenericName", "NoDisplay",
           "Comment", "Icon",     "Hidden", "TryExec",     "Exec",
           "Path",    "Terminal", "URL"};
    QStringList knownListProperties = {"Categories", "Keywords", "MimeType"};

    settings.beginGroup("Desktop Entry");
    for (auto &prop : knownProperties) {
        QVariant value = property(prop.toUtf8().constData());
        if (!value.isNull() && !value.toString().isEmpty())
            settings.setValue(prop, value.toString());
    }
    for (auto &prop : knownListProperties) {
        QVariant value = property(prop.toUtf8().constData());
        if (!value.isNull() && !value.toStringList().isEmpty())
            settings.setValue(prop, value.toStringList().join(';'));
    }
    settings.endGroup();

    settings.sync();

    return settings.status() == QSettings::NoError ? fileName : "";
}


/**
 * @fn removeDesktop
 */
bool ApplicationItem::removeDesktop(const QString &_desktopPath) const
{
    qCDebug(LOG_LIB) << "Desktop path" << _desktopPath;

    QString fileName = QString("%1/%2").arg(_desktopPath).arg(desktopName());

    return QFile::remove(fileName);
}


/**
 * @fn run
 */
bool ApplicationItem::run(const QVariantHash &_args) const
{
    qCDebug(LOG_LIB) << "Program arguments" << _args;

    // build cmd
    QStringList cmdArgs = generateExec(_args);
    QString cmd = cmdArgs.takeFirst();

    return QProcess::startDetached(cmd, cmdArgs,
                                   m_path.isEmpty() ? "/" : m_path);
}
