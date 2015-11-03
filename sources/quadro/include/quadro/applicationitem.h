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
 * @file applicationitem.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef APPLICATIONITEM_H
#define APPLICATIONITEM_H

#include <QObject>
#include <QVariant>


class QIcon;

/**
 * @brief The ApplicationItem class provides launcher items
 * @remark implementation of
 * http://standards.freedesktop.org/desktop-entry-spec/latest/ar01s05.html
 * @note keys OnlyShowIn, NotShowIn, DBusActivatable, Actions. Implements,
 * StartupNotify, StartupWMClass are not supported (yet?)
 */
class ApplicationItem : public QObject
{
    Q_OBJECT
    // properties declared in spec
    Q_PROPERTY(QString Type READ type WRITE setType)
    Q_PROPERTY(QString Version READ version WRITE setVersion)
    Q_PROPERTY(QString Name READ name WRITE setName)
    Q_PROPERTY(QString GenericName READ genericName WRITE setGenericName)
    Q_PROPERTY(bool NoDisplay READ noDisplay WRITE setNoDisplay)
    Q_PROPERTY(QString Comment READ comment WRITE setComment)
    Q_PROPERTY(QString Icon READ icon WRITE setIcon)
    Q_PROPERTY(bool Hidden READ isHidden WRITE setHidden)
    Q_PROPERTY(QString TryExec READ tryExec WRITE setTryExec)
    Q_PROPERTY(QString Exec READ exec WRITE setExec)
    Q_PROPERTY(QString Path READ path WRITE setPath)
    Q_PROPERTY(bool Terminal READ terminal WRITE setTerminal)
    Q_PROPERTY(QStringList MimeType READ mimeType WRITE setMimeType)
    Q_PROPERTY(QStringList Categories READ categories WRITE setCategories)
    Q_PROPERTY(QStringList Keywords READ keywords WRITE setKeywords)
    Q_PROPERTY(QString URL READ url WRITE setUrl)
    // custom properties
    Q_PROPERTY(bool shouldBeShown READ shouldBeShown)

public:
    /**
     * @brief ApplicationItem class constructor
     * @param parent         pointer to parent item
     * @param name           application name
     */
    explicit ApplicationItem(QObject *parent, const QString name);
    /**
     * @brief ApplicationItem class destructor
     */
    virtual ~ApplicationItem();
    // get methods
    /**
     * @brief application categories
     * @return list of categories
     */
    QStringList categories() const;
    /**
     * @brief application comment
     * @return comment in system locale or English
     */
    QString comment() const;
    /**
     * @brief full application executable path
     * @return full executable path
     */
    QString exec() const;
    /**
     * @brief application generic name
     * @return generic name
     */
    QString genericName() const;
    /**
     * @brief is application hidden
     * @return true if application is hidden otherwise returns false
     */
    bool isHidden() const;
    /**
     * @brief application icon name
     * @return icon name
     */
    QString icon() const;
    /**
     * @brief application keywords
     * @return list of keywords
     */
    QStringList keywords() const;
    /**
     * @brief associated application mime types
     * @return mime type list
     */
    QStringList mimeType() const;
    /**
     * @brief application name
     * @return name
     */
    QString name() const;
    /**
     * @brief should application be shown or not
     * @return true if application should not be shown otherwise returns false
     */
    bool noDisplay() const;
    /**
     * @brief application working directory
     * @return path to working directory
     */
    QString path() const;
    /**
     * @brief url for link type
     * @return url as string
     */
    QString url() const;
    /**
     * @brief should application be run from terminal or not
     * @return true if application should be run from terminal otherwise returns false
     */
    bool terminal() const;
    /**
     * @brief test executable for the application
     * @return test executable name
     */
    QString tryExec() const;
    /**
     * @brief desktop entry type
     * @return desktop entry type in Application, Link, Directory
     */
    QString type() const;
    /**
     * @brief desktop entry specification version
     * @return version as QString
     */
    QString version() const;
    // set methods
    /**
     * @brief set application categories
     * @param _categories    application categories
     */
    void setCategories(const QStringList _categories);
    /**
     * @brief set application comment
     * @param _comment       application comment
     */
    void setComment(const QString _comment);
    /**
     * @brief set executable for application
     * @param _exec       executable name
     */
    void setExec(const QString _exec);
    /**
     * @brief set application generic name
     * @param _genericName   application generic name
     */
    void setGenericName(const QString _genericName);
    /**
     * @brief set is application hidden or not
     * @param _hidden        is application hidden
     */
    void setHidden(const bool _hidden);
    /**
     * @brief set application icon from string
     * @param _icon          name of icon
     */
    void setIcon(const QString _icon);
    /**
     * @brief set application keywords
     * @param _keywords      application keywords
     */
    void setKeywords(const QStringList _keywords);
    /**
     * @brief set application mime types
     * @param _mimeTypes     application mime types
     */
    void setMimeType(const QStringList _mimeType);
    /**
     * @brief set application name
     * @remark if _name is empty it will be assigned from executable
     * @param _name          application name
     */
    void setName(const QString _name);
    /**
     * @brief set should application be shown or not
     * @param _noDisplay     false if application should be shown
     */
    void setNoDisplay(const bool _noDisplay);
    /**
     * @brief set application working directory
     * @param _path          working directory
     */
    void setPath(const QString _path);
    /**
     * @brief set url for link type
     * @param _url           desktop entry url
     */
    void setUrl(const QString _url);
    /**
     * @brief set should application be run from terminal or not
     * @param _terminal      true if application should be run from terminal
     */
    void setTerminal(const bool _terminal);
    /**
     * @brief set test executable for application
     * @param _tryExec       test executable name
     */
    void setTryExec(const QString _tryExec);
    /**
     * @brief set desktop entry type
     * @param _type          new desktop entry type
     */
    void setType(QString _type);
    /**
     * @brief set desktop entry specification version
     * @param _version       specification version
     */
    void setVersion(const QString _version);
    // desktop methods
    /**
     * @brief application icon as QIcon object
     * @return QIcon object associated with ApplicationItem::icon()
     */
    QIcon appIcon() const;
    /**
     * @brief define list from desktop file
     * @remark this method is required because the standard Qt codec uses ; as
     * separator
     * @param _desktopPath   full path to desktop file
     * @param _key           key for search
     * @return list of found values by key
     */
    static QStringList defineList(const QString _desktopPath, const QString _key);
    /**
     * @brief desktop name
     * @return recommended name of desktop file
     */
    QString desktopName() const;
    /**
     * @brief read application information from desktop file
     * @param _desktopPath   full path to desktop file
     * @param _parent        pointer to parent item
     * @return ApplicationItem structure
     */
    static ApplicationItem *fromDesktop(const QString _desktopPath, QObject *_parent);
    /**
     * @brief does application have specified substring or not
     * @param _substr        substring for search
     * @return true if comment or name is equal to substring otherwise returns false
     */
    bool hasSubstring(const QString _substr) const;
    /**
     * @brief set desktop name
     * @param _desktopName   name of desktop file
     */
    void setDesktopName(const QString _desktopName);
    /**
     * @brief additional method indicates should application be shown in the menu
     * or not
     * @return true if application should not be shown otherwise returns false
     */
    bool shouldBeShown() const;
    /**
     * @brief is application start with substring
     * @param _substr        substring for search
     * @return true if executable starts with substring otherwise returns false
     */
    bool startsWith(const QString _substr) const;

public slots:
    /**
     * @brief launch the application
     */
    bool launch(const QVariantHash args = QVariantHash()) const;
    /**
     * @brief write settings to desktop file
     * @param _desktopPath   full path to desktop file
     * @return full path to created file or empty string
     */
    QString saveDesktop(const QString _desktopPath) const;
    /**
     * @brief remove desktop file from path
     * @param _desktopPath   full path to desktop file
     * @return true if file has been removed otherwise returns false
     */
    bool removeDesktop(const QString _desktopPath) const;

private slots:
    /**
     * @brief run application
     */
    bool run(const QVariantHash args = QVariantHash()) const;

private:
    // main
    // properties
    /**
     * @brief application categories
     */
    QStringList m_categories = QStringList();
    /**
     * @brief application comment in default system locale or English
     */
    QString m_comment = QString();
    /**
     * @brief name of desktop file if any
     */
    QString m_desktopName = QString();
    /**
     * @brief application generic name
     */
    QString m_genericName = QString();
    /**
     * @brief application executable
     */
    QString m_exec = QString();
    /**
     * @brief is application hidden
     */
    bool m_hidden = false;
    /**
     * @brief application icon
     */
    QString m_icon = QString("system-run");
    /**
     * @brief application keywords
     */
    QStringList m_keywords = QStringList();
    /**
     * @brief application mime types
     */
    QStringList m_mimeType = QStringList();
    /**
     * @brief application name
     */
    QString m_name = QString();
    /**
     * @brief should application be shown or not
     */
    bool m_noDisplay = false;
    /**
     * @brief application working directory
     */
    QString m_path = QString();
    /**
     * @brief url for link application type
     */
    QString m_url = QString();
    /**
     * @brief should application be run from terminal or not
     */
    bool m_terminal = false;
    /**
     * @brief test application executable
     */
    QString m_tryExec = QString();
    /**
     * @brief desktop type
     */
    QString m_type = QString("Application");
    /**
     * @brief version of specification
     */
    QString m_version = QString("1.0");
};


#endif /* APPLICATIONITEM_H */
