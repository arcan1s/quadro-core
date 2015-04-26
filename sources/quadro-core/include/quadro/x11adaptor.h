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
 * @file x11adaptor.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef X11ADAPTOR_H
#define X11ADAPTOR_H

#include <QMap>
#include <QObject>
#include <QX11Info>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

#define MAX_PROPERTY_VALUE_LEN 4096


/**
 * @brief The X11Adaptor class provides adaptor to the common X11 calls
 * @remark this class is adapted from wmctrl https://sites.google.com/site/tstyblo/wmctrl
 */
class X11Adaptor : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief X11Adaptor class constructor
     * @param parent         pointer to parent item
     * @param debugCmd       show debug messages
     */
    explicit X11Adaptor(QObject *parent, const bool debugCmd = false);
    /**
     * @brief X11Adaptor class destructor
     */
    ~X11Adaptor();
    /**
     * @brief get active windows
     * @return map of windows keys of which are Q_PIDs
     */
    QMap<long long, unsigned long> getWindowsList();

public slots:

private:
    /**
     * @brief show debug messages. Default is false
     */
    bool debug = false;
    /**
     * @brief get client list
     * @return client list
     */
    Window *getClientList(unsigned long *size);
    /**
     * @brief get propery by window
     * @return propery
     */
    char *getPropery(const Window _win, const Atom _xaPropType,
                     const char *_propery, unsigned long *size);
};


#endif /* X11ADAPTOR_H */
