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


#ifndef QUADROUIADAPTOR_H
#define QUADROUIADAPTOR_H

#include <QDBusAbstractAdaptor>

#include "config.h"


class QuadroMainWindow;

class QuadroUiAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", DBUS_INTERFACE)

public:
    explicit QuadroUiAdaptor(QuadroMainWindow *parent);
    virtual ~QuadroUiAdaptor();

public slots:
    bool Active() const;
    void ChangeState() const;
    void Close() const;
    void Hide() const;
    void Restore() const;
    void RunContainer(const QStringList exec, const QString name = QString()) const;
    void RunWebContainer(const QString url, const bool showOpen) const;
    QStringList UIDs() const;

private:
    QuadroMainWindow *m_mainWindow = nullptr;
};


#endif /* QUADROUIADAPTOR_H */
