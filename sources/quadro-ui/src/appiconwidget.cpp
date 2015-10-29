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


#include <QApplication>
#include <QMenu>

#include "appiconwidget.h"


AppIconWidget::AppIconWidget(ApplicationItem *appItem, const QSize size,
                             QWidget *parent)
    : IconWidget(size, parent),
      item(appItem)
{
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;

    setIcon(item->icon());
    setText(item->name());
    createActions();

    connect(this, SIGNAL(widgetPressed()), this, SLOT(run()));
}


AppIconWidget::~AppIconWidget()
{
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;

    delete m_menu;
}


ApplicationItem *AppIconWidget::associatedItem()
{
    return item;
}


void AppIconWidget::showContextMenu(const QPoint &pos)
{
    m_menu->popup(mapToGlobal(pos));
}


void AppIconWidget::run()
{
    item->launch();
}


void AppIconWidget::runInNewTab()
{
    // TODO
}


void AppIconWidget::createActions()
{
    m_menu = new QMenu(this);

    m_menu->addAction(QIcon::fromTheme(QString("system-run")),
                      QApplication::translate("AppIconWidget", "Run application"),
                      this, SLOT(run()));
    m_menu->addAction(QIcon::fromTheme(QString("system-run")),
                      QApplication::translate("AppIconWidget", "Run application in new tab"),
                      this, SLOT(runInNewTab()));
    m_menu->addAction(QIcon::fromTheme(QString("emblem-favorites")),
                      QApplication::translate("AppIconWidget", "Add to favorites"),
                      this, SLOT(runInNewTab()));
}
