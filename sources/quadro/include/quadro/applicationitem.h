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

#include <QIcon>
#include <QObject>


/**
 * @brief The ApplicationItem class provides launcher items
 */
class ApplicationItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList categories READ categories WRITE setCategories)
    Q_PROPERTY(QString comment READ comment WRITE setComment)
    Q_PROPERTY(QString executable READ executable)
    Q_PROPERTY(bool hidden READ isHidden WRITE setHidden)
    Q_PROPERTY(QIcon icon READ icon WRITE setIcon)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(bool noDesktop READ noDesktop WRITE setNoDesktop)
    Q_PROPERTY(bool shouldBeShown READ shouldBeShown)

public:
    /**
     * @brief ApplicationItem class constructor
     * @param parent         pointer to parent item
     * @param exePath        full path to executable file
     * @param name           application name. If name is not given it will be
     *                       assigned from exePath
     */
    explicit ApplicationItem(QObject *parent,
                             const QString exePath,
                             const QString name = QString());
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
     * @brief desktop name
     * @return recommended name of desktop file
     */
    QString desktopName() const;
    /**
     * @brief full application executable path
     * @return full executable path
     */
    QString executable() const;
    /**
     * @brief does application have specified substring or not
     * @param _substr        substring for search
     * @return true if comment or name is equal to substring
     * @return false if comment or name is not found
     */
    bool hasSubstring(const QString _substr) const;
    /**
     * @brief is application hidden
     * @return true if application is hidden
     * @return false if application is not hidden
     */
    bool isHidden() const;
    /**
     * @brief application icon
     * @return icon
     */
    QIcon icon() const;
    /**
     * @brief application name
     * @return name
     */
    QString name() const;
    /**
     * @brief should application be shown or not
     * @return true if application should not be shown
     * @return false if application should be shown
     */
    bool noDesktop() const;
    /**
     * @brief additional method indicates should application be shown in the menu
     * or not
     * @return true if application should not be shown
     * @return false if application should be shown
     */
    bool shouldBeShown() const;
    /**
     * @brief is application start with substring
     * @param _substr        substring for search
     * @return true if executable starts with substring
     * @return false if executable doesn't start with substring
     */
    bool startsWith(const QString _substr) const;
    // set methods
    /**
     * @brief set application categories
     * @param _categories    application categories
     */
    void setCategories(const QStringList _categories = QStringList());
    /**
     * @brief set application comment
     * @param _comment       application comment
     */
    void setComment(const QString _comment = QString());
    /**
     * @brief set desktop name
     * @param _desktopName   name of desktop file
     */
    void setDesktopName(const QString _desktopName = QString());
    /**
     * @brief set is application hidden or not
     * @param _hidden        is application hidden
     */
    void setHidden(const bool _hidden = false);
    /**
     * @brief set application icon
     * @param _icon          application icon
     */
    void setIcon(const QIcon _icon = QIcon());
    /**
     * @brief set application icon from string
     * @param _iconName      name of icon
     */
    void setIconByName(const QString _iconName = QString());
    /**
     * @brief set application name
     * @remark if _name is empty it will be assigned from executable
     * @param _name          application name
     */
    void setName(const QString _name = QString());
    /**
     * @brief set should application be shown or not
     * @param _noDesktop     false if application should be shown
     */
    void setNoDesktop(const bool _noDesktop = false);
    // desktop methods
    /**
     * @brief read application information from desktop file
     * @param _desktopPath   full path to desktop file
     * @param _parent        pointer to parent item
     * @param debugCmd       show debug messages
     * @return ApplicationItem structure
     */
    static ApplicationItem *fromDesktop(const QString _desktopPath, QObject *_parent);

public slots:
    /**
     * @brief define categories list from desktop file
     * @param _desktopPath   full path to desktop file
     */
    void defineCategories(const QString _desktopPath);
    /**
     * @brief launch the application
     * @return status of the running application
     */
    bool launch() const;
    /**
     * @brief write settings to desktop file
     * @param _desktopPath   full path to desktop file
     * @return full path to created file or empty string
     */
    QString saveDesktop(const QString _desktopPath) const;

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
     * @brief application executable
     */
    QString m_executable;
    /**
     * @brief is application hidden
     */
    bool m_hidden;
    /**
     * @brief application icon
     */
    QIcon m_icon = QIcon::fromTheme(QString("system-run"));
    /**
     * @brief application name
     */
    QString m_name = QString();
    /**
     * @brief should application be shown or not
     */
    bool m_noDesktop;
};


#endif /* APPLICATIONITEM_H */
