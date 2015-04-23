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
#include <QObject>

#include "version.h"


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
     * @param debugCmd       show debug messages
     */
    explicit QuadroAdaptor(QuadroCore *core,
                           const bool debugCmd = false);
    /**
     * @brief QuadroAdaptor class destructor
     */
    ~QuadroAdaptor();

public slots:

signals:

private:
    /**
     * @brief show debug messages. Default is false
     */
    bool debug = false;
    // properties
    /**
     * @brief pointer to the core
     */
    QuadroCore *m_core = nullptr;
};


#endif /* QuadroAdaptor */
