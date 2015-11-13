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
 * @file quadroadaptor.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef QUADROADAPTOR_H
#define QUADROADAPTOR_H

#include <QDBusAbstractAdaptor>

#include "config.h"


class QuadroCore;

/**
 * @brief The QuadroAdaptor class provides core DBus adaptor
 */
class QuadroAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", DBUS_INTERFACE)

public:
    /**
     * @brief QuadroAdaptor class constructor
     * @param core           pointer to core part
     */
    explicit QuadroAdaptor(QuadroCore *core);
    /**
     * @brief QuadroAdaptor class destructor
     */
    virtual ~QuadroAdaptor();

public slots:
    /**
     * @brief favorites applications list
     * @return list of applicaiton from FavoritesCore
     */
    QStringList Favorites() const;
    /**
     * @brief get icon by file path
     * @param _file          absolute file path
     * @return icon name of the specified file
     */
    QString Icon(const QString _file) const;
    /**
     * @brief check if there is a known plugin for this platform
     * @return true if DesktopInterface has been initialized
     */
    bool IsKnownPlatform() const;
    /**
     * @brief get mime name by file path
     * @param _file          absolute file path
     * @return mime name of the specified file
     */
    QString MIME(const QString _file) const;
    /**
     * @brief recent applications list
     * @return list of application from RecentlyCore
     */
    QStringList Recent() const;
    /**
     * @brief update application list
     */
    void UpdateApplications() const;
    /**
     * @brief update favorites applications list
     */
    void UpdateFavorites() const;
    /**
     * @brief update recently run applications
     */
    void UpdateRecent() const;
    /**
     * @brief get WIds by given PID
     * @remark since C++ doesn't allow static pure methods...
     * @param _pid           PID
     * @return list of WIds as QString reresentation
     */
    QStringList WIdForPID(const long long _pid);

signals:

private:
    // properties
    /**
     * @brief pointer to the core
     */
    QuadroCore *m_core = nullptr;
};


#endif /* QuadroAdaptor */
