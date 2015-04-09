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
    Q_PROPERTY(QIcon icon READ icon WRITE setIcon)
    Q_PROPERTY(QString name READ name WRITE setName)

public:
    /**
     * @brief ApplicationItem class constructor
     * @param exePath        full path to executable file
     * @param name           application name. If name is not given it will be
     *                       assigned from exePath
     * @param debugCmd       show debug messages
     */
    explicit ApplicationItem(const QString exePath,
                             const QString name = QString(),
                             const bool debugCmd = false);
    /**
     * @brief ApplicationItem class destructor
     */
    ~ApplicationItem();
    // get methods
    /**
     * @brief returns application categories
     * @return list of categories
     */
    QStringList categories();
    /**
     * @brief returns application comment
     * @return comment in system locale or English
     */
    QString comment();
    /**
     * @brief returns full application executable path
     * @return full executable path
     */
    QString executable();
    /**
     * @brief returns application icon
     * @return icon
     */
    QIcon icon();
    /**
     * @brief returns application name
     * @return name
     */
    QString name();
    // set methods
    /**
     * @brief sets application categories
     * @param _categories    application categories
     */
    void setCategories(const QStringList _categories = QStringList());
    /**
     * @brief sets application comment
     * @param _comment       application comment
     */
    void setComment(const QString _comment = QString());
    /**
     * @brief sets application icon
     * @param _icon          application icon
     */
    void setIcon(const QIcon _icon = QIcon());
    /**
     * @brief sets application icon from string
     * @param _iconName      name of icon
     */
    void setIconByName(const QString _iconName = QString());
    /**
     * @brief sets application name
     * @remark if _name is empty it will be assigned from executable
     * @param _name          application name
     */
    void setName(const QString _name = QString());
    // desktop methods
    /**
     * @brief reads application information from desktop file
     * @param _desktopPath   full path to desktop file
     * @return ApplicationItem structure
     */
    static ApplicationItem *fromDesktop(const QString _desktopPath);
    /**
     * @brief write settings to desktop file
     * @return full path to created file or empty string
     */
    QString saveDesktop();

private:
    // main
    /**
     * @brief show debug messages. Default is false
     */
    bool debug = false;
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
     * @brief application executable
     */
    QString m_executable;
    /**
     * @brief application icon
     */
    QIcon m_icon = QIcon();
    /**
     * @brief application name
     */
    QString m_name = QString();
};


#endif /* APPLICATIONITEM_H */
