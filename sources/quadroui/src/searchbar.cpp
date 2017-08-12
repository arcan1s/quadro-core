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
 * @file searchbar.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadroui/quadroui.h"

#include <QKeyEvent>

#include <quadrocore/quadrodebug.h>


/**
 * @class SearchBar
 */
/**
 * @fn SearchBar
 */
SearchBar::SearchBar(QWidget *_parent)
    : QLineEdit(_parent)
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;

    setAlignment(Qt::AlignCenter);
    setContextMenuPolicy(Qt::NoContextMenu);
    setFocusPolicy(Qt::NoFocus);
    setReadOnly(true);
}


/**
 * @fn ~SearchBar
 */
SearchBar::~SearchBar()
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;
}


/**
 * @fn keyPressed
 */
void SearchBar::keyPressed(QKeyEvent *_event)
{
    if (_event->key() == Qt::Key_Backspace) {
        backspace();
    } else if ((_event->key() == Qt::Key_Return)
               || (_event->key() == Qt::Key_Enter)) {
        emit(returnPressed());
    } else if (_event->key() == Qt::Key_Delete) {
        clear();
    } else {
        updateText(_event->text(), _event->modifiers());
    }
}


/**
 * @fn keyPressEvent
 */
void SearchBar::keyPressEvent(QKeyEvent *_pressedKey)
{
    keyPressed(_pressedKey);

    return QLineEdit::keyPressEvent(_pressedKey);
}


/**
 * @fn updateText
 */
void SearchBar::updateText(const QString &_text, Qt::KeyboardModifiers _mods)
{
    qCDebug(LOG_UILIB) << "Received text" << _text;
    if ((_mods != Qt::NoModifier) && (_mods != Qt::ShiftModifier)) {
        qCInfo(LOG_UILIB) << "Skip due to modifiers enabled";
        return;
    }

    return setText(text() + _text.toLower());
}
