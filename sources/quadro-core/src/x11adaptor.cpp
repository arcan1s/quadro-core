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
 * @file x11adaptor.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include <QDebug>

#include <quadro/quadro.h>
#include <pdebug/pdebug.h>

#include <X11/Xatom.h>
#include <X11/Xlib.h>



/**
 * @class X11Adaptor
 */
/**
 * @fn X11Adaptor
 */
X11Adaptor::X11Adaptor(QObject *parent, const bool debugCmd)
    : QObject(parent),
      debug(debugCmd)
{
}


/**
 * @fn ~X11Adaptor
 */
X11Adaptor::~X11Adaptor()
{
    if (debug) qDebug() << PDEBUG;
}


/**
 * @fn getWindowsList
 */
QMap<long long, unsigned long long> X11Adaptor::getWindowsList(const bool debugCmd)
{
    if (debugCmd) qDebug() << PDEBUG;

    QMap<long long, unsigned long long> windows;
    if (QX11Info::display() == nullptr) return windows;

    X11Adaptor *instance = new X11Adaptor(nullptr, debugCmd);
    unsigned long clientListSize;
    Window *clientList = instance->getClientList(&clientListSize);
    if (clientList == nullptr) {
        delete instance;
        return windows;
    }

    for (unsigned int i=0; i<clientListSize / sizeof(Window); i++) {
        long long *pid = (long long *)instance->getPropery(clientList[i], XA_CARDINAL,
                                                           "_NET_WM_PID", nullptr);
        windows[*pid] = clientList[i];
    }

    delete instance;
    return windows;
}


Window *X11Adaptor::getClientList(unsigned long *size)
{
    if (debug) qDebug() << PDEBUG;

    Window *clientList = nullptr;
    if ((clientList = (Window *)getPropery(DefaultRootWindow(QX11Info::display()),
                                           XA_WINDOW, "_NET_CLIENT_LIST", size)) == nullptr)
        if ((clientList = (Window *)getPropery(DefaultRootWindow(QX11Info::display()),
                                               XA_CARDINAL, "_WIN_CLIENT_LIST", size)) == nullptr) {
            if (debug) qDebug() << PDEBUG << ":" << "Could not get properties _NET_CLIENT_LIST or _WIN_CLIENT_LIST";
            return nullptr;
        }

    return clientList;
}


char *X11Adaptor::getPropery(const Window _win, const Atom _xaPropType,
                             const char *_propery, unsigned long *size)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << ":" << "Property" << _propery;

    Atom xaPropName = XInternAtom(QX11Info::display(), _propery, false);

    Atom xaRetType;
    int retFormat;
    unsigned long retBytesAfter;
    unsigned long retNitems;
    unsigned char *retProperty;
    if (XGetWindowProperty(QX11Info::display(), _win, xaPropName, 0,
                           MAX_PROPERTY_VALUE_LEN / 4, false,
                           _xaPropType, &xaRetType, &retFormat,
                           &retNitems, &retBytesAfter, &retProperty) != Success) {
        if (debug) qDebug() << PDEBUG << ":" << "Could not get property" << _propery;
        return nullptr;
    }

    if (xaRetType != _xaPropType) {
        if (debug) qDebug() << PDEBUG << ":" << "Invalid property name" << _propery;
        XFree(retProperty);
        return nullptr;
    }

    if (size != nullptr)
        *size = (retFormat / 8) * retNitems;
    return reinterpret_cast<char *>(retProperty);
}
