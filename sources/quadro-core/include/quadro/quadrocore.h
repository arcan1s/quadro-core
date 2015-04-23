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
 * @file quadrocore.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef QUADROCORE_H
#define QUADROCORE_H

#include <QObject>


/**
 * @brief The QuadroCore class provides Quadro backend
 */
class QuadroCore : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief QuadroCore class constructor
     * @param parent         pointer to parent item
     * @param debugCmd       show debug messages
     */
    explicit QuadroCore(QObject *parent, const bool debugCmd = false);
    /**
     * @brief QuadroCore class destructor
     */
    ~QuadroCore();

public slots:

private:
    /**
     * @brief show debug messages. Default is false
     */
    bool debug = false;
};


#endif /* QUADROCORE_H */
