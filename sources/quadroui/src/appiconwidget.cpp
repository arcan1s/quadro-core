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
 * @file appiconwidget.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadroui/quadroui.h"

#include <QMenu>
#include <QMessageBox>
#include <QMouseEvent>
#include <QStandardPaths>

#include <quadrocore/quadro.h>


/**
 * @class AppIconWidget
 */
/**
 * @fn AppIconWidget
 */
AppIconWidget::AppIconWidget(ApplicationItem *appItem, const QSize size,
                             QWidget *parent)
    : IconWidget(size, parent),
      m_item(appItem)
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;

    setIcon(m_item->appIcon());
    setText(m_item->name());
    QStringList tooltip;
    if (!m_item->genericName().isEmpty())
        tooltip.append(m_item->genericName());
    if (!m_item->comment().isEmpty())
        tooltip.append(m_item->comment());
    setToolTip(tooltip.join(QChar('\n')));
    createActions();

    connect(this, SIGNAL(widgetPressed()), this, SLOT(run()));
}


/**
 * @fn~ AppIconWidget
 */
AppIconWidget::~AppIconWidget()
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;

    delete m_menu;
}


/**
 * @fn associatedItem
 */
ApplicationItem *AppIconWidget::associatedItem()
{
    return m_item;
}


/**
 * @fn showContextMenu
 */
void AppIconWidget::showContextMenu(const QPoint &_pos)
{
    m_menu->popup(mapToGlobal(_pos));
}


/**
 * @fn mousePressEvent
 */
void AppIconWidget::mousePressEvent(QMouseEvent *_event)
{
    if (_event->button() == Qt::MiddleButton) {
        emit(runInNewTab());
    }

    QWidget::mousePressEvent(_event);
}


/**
 * @fn addItemToFavorites
 */
void AppIconWidget::addItemToFavorites()
{
    FavoritesCore::addToFavorites(m_item);
    DBusOperations::sendRequestToLibrary(QString("UpdateFavorites"));
}


/**
 * @fn editApplication
 */
void AppIconWidget::editApplication()
{
    EditAppWindow *editWindow = new EditAppWindow(this, m_item);

    return editWindow->showWindow();
}


/**
 * @fn hideApplication
 */
void AppIconWidget::hideApplication()
{
    m_item->setNoDisplay(true);
    m_item->saveDesktop(QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation));
}


/**
 * @fn run
 */
void AppIconWidget::run()
{
    if (m_item->launch())
        DBusOperations::sendRequestToUi(QString("Hide"));
    else
        QMessageBox::critical(this, tr("Error"),
                              tr("Error"),
                              tr("Could not run application %1").arg(m_item->exec()));
}


/**
 * @fn runInNewTab
 */
void AppIconWidget::runInNewTab()
{
    DBusOperations::sendRequestToUi(QString("RunContainer"), QVariantList() << m_item->exec()
        << m_item->name());
}


/**
 * @fn createActions
 */
void AppIconWidget::createActions()
{
    m_menu = new QMenu(this);

    m_menu->addAction(QIcon::fromTheme(QString("system-run")),
                      tr("Run application"),
                      this, SLOT(run()));
    m_menu->addAction(QIcon::fromTheme(QString("system-run")),
                      tr("Run application in new tab"),
                      this, SLOT(runInNewTab()));
    m_menu->addAction(QIcon::fromTheme(QString("emblem-favorites")),
                      FavoritesCore::hasApplication(m_item) ?
                      tr("Remove from favorites") :
                      tr("Add to favorites"),
                      this, SLOT(addItemToFavorites()));
    m_menu->addSeparator();

    m_menu->addAction(tr("Edit"), this, SLOT(editApplication()));
    m_menu->addAction(tr("Hide"), this, SLOT(hideApplication()));
}
