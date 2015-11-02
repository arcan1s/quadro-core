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


#ifndef DBUSOPERATION_H
#define DBUSOPERATION_H

#include <QVariant>


QVariantList sendRequest(const QString service, const QString path, const QString interface,
                         const QString cmd, const QVariantList args);
QVariantList sendRequestToLibrary(const QString cmd, const QVariantList args = QVariantList());
QVariantList sendRequestToPlugin(const QString plugin, const QString cmd,
                                 const QVariantList args = QVariantList());
QVariantList sendRequestToUi(const QString cmd, const QVariantList args = QVariantList());


#endif /* DBUSOPERATION_H */
