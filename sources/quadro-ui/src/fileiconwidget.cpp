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


#include "fileiconwidget.h"

#include <QIcon>

#include "quadro/quadrodebug.h"


FileIconWidget::FileIconWidget(const QFileInfo info, const QIcon icon,
                               const QSize size, QWidget *parent)
    : IconWidget(size, parent)
    , m_info(info)
{
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;

    setIcon(icon);
    setText(m_info.fileName());

    connect(this, &IconWidget::widgetPressed, [this]() {
        emit(openFile(m_info));
    });
}


FileIconWidget::~FileIconWidget()
{
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;
}
