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
 * @file quadroxcbadaptor.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadroxcbadaptor.h"

#include <QX11Info>

#include <X11/Xatom.h>
#include <X11/Xlib.h>

#include <quadrocore/quadro.h>


/**
 * @class QuadroXCBAdaptor
 */
/**
 * @fn ~QuadroXCBAdaptor
 */
QuadroXCBAdaptor::~QuadroXCBAdaptor()
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;
}


/**
 * @fn getWindowByPid
 */
QList<unsigned long long> QuadroXCBAdaptor::getWindowByPid(const long long _pid)
{
    if (QX11Info::display() == nullptr) {
        qCCritical(LOG_LIB) << "Could not connect to display";
        return QList<unsigned long long>();
    }

    return getWindowsList().values(_pid);
}


/**
 * @fn getWindowsList
 */
QHash<long long, unsigned long long> QuadroXCBAdaptor::getWindowsList()
{
    QHash<long long, unsigned long long> windows;

    unsigned long clientListSize;
    Window *clientList = getClientList(&clientListSize);
    if (clientList == nullptr) {
        qCCritical(LOG_LIB) << "Could not get client list";
        return windows;
    }

    for (unsigned int i=0; i<clientListSize / sizeof(Window); i++) {
        long long *pid = reinterpret_cast<long long *>(getPropery(clientList[i], XA_CARDINAL,
                                                                  "_NET_WM_PID", nullptr));
        windows.insertMulti(*pid, clientList[i]);
    }

    return windows;
}


Window *QuadroXCBAdaptor::getClientList(unsigned long *size) const
{
    qCDebug(LOG_LIB) << "Size" << size;

    char *clientList = nullptr;
    if ((clientList = getPropery(DefaultRootWindow(QX11Info::display()),
                                 XA_WINDOW, "_NET_CLIENT_LIST", size)) == nullptr) {
        if ((clientList = getPropery(DefaultRootWindow(QX11Info::display()),
                                     XA_CARDINAL, "_WIN_CLIENT_LIST", size)) == nullptr) {
            qCCritical(LOG_LIB) << "Could not get properties _NET_CLIENT_LIST or _WIN_CLIENT_LIST";
            return nullptr;
        }
    }

    return reinterpret_cast<Window *>(clientList);
}


char *QuadroXCBAdaptor::getPropery(const Window _win, const Atom _xaPropType,
                                   const char *_property, unsigned long *size) const
{
    qCDebug(LOG_LIB) << "Property" << _property;

    Atom xaPropName = XInternAtom(QX11Info::display(), _property, False);

    Atom xaRetType;
    int retFormat;
    unsigned long retBytesAfter;
    unsigned long retNItems;
    unsigned char *retProperty;
    if (XGetWindowProperty(QX11Info::display(), _win, xaPropName, 0,
                           MAX_PROPERTY_VALUE_LEN / 4, false,
                           _xaPropType, &xaRetType, &retFormat,
                           &retNItems, &retBytesAfter, &retProperty) != Success) {
        qCCritical(LOG_LIB) << ":" << "Could not get property" << _property;
        return nullptr;
    }

    if (xaRetType != _xaPropType) {
        qCCritical(LOG_LIB) << "Invalid property name" << _property;
        XFree(retProperty);
        return nullptr;
    }

    if (size != nullptr)
        *size = (retFormat / 4) * retNItems;
    return reinterpret_cast<char *>(retProperty);
}
