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
 * @file SearchBar.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QLineEdit>


/**
 * @namespace Quadro
 */
namespace Quadro
{
/**
 * @brief The SearchBar class provides search line for plugins
 */
class SearchBar : public QLineEdit
{
    Q_OBJECT

public:
    /**
     * @brief SearchBar class constructor
     * @param _parent pointer to parent object
     */
    explicit SearchBar(QWidget *parent);

    /**
     * @brief SearchBar class destructor
     */
    virtual ~SearchBar();

    /**
     * @brief method which should be called to pass key press event
     * @param _event pointer to event object
     */
    void keyPressed(QKeyEvent *_event);

protected:
    /**
     * @brief method which will be called on key press event
     * @param _pressedKey pointer to pressed key
     */
    void keyPressEvent(QKeyEvent *_pressedKey);

private:
    /**
     * @brief pass text to line
     * @remark this method should not get any modifiers as input
     * @param _text generated text
     * @param _mods pressed key modifiers
     */
    void updateText(const QString &_text, Qt::KeyboardModifiers _mods);
};
};


#endif /* SEARCHBAR_H */
