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
 * @file quadroadaptor.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadrocore/quadro.h"


/**
 * @class QuadroAdaptor
 */
/**
 * @fn QuadroAdaptor
 */
QuadroAdaptor::QuadroAdaptor(QuadroCore *core)
    : QDBusAbstractAdaptor(core),
      m_core(core)
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;
}


/**
 * @fn ~QuadroAdaptor
 */
QuadroAdaptor::~QuadroAdaptor()
{
    qCDebug(LOG_LIB) << __PRETTY_FUNCTION__;
}


/**
 * @fn UpdateFavorites
 */
void QuadroAdaptor::UpdateFavorites() const
{
    m_core->favorites()->initApplications();
}


/**
 * @fn UpdateRecent
 */
void QuadroAdaptor::UpdateRecent() const
{
    m_core->recently()->initApplications();
}
