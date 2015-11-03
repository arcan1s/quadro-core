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
#include <QMessageBox>
#include <QMouseEvent>
#include <QStandardPaths>

#include "appiconwidget.h"
#include "applauncherwidget.h"
#include "dbusoperation.h"
#include "editappwindow.h"


AppIconWidget::AppIconWidget(ApplicationItem *appItem, const QSize size,
                             QWidget *parent)
    : IconWidget(size, parent),
      m_item(appItem)
{
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;

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


AppIconWidget::~AppIconWidget()
{
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;

    delete m_menu;
}


ApplicationItem *AppIconWidget::associatedItem()
{
    return m_item;
}


void AppIconWidget::showContextMenu(const QPoint &pos)
{
    m_menu->popup(mapToGlobal(pos));
}


void AppIconWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton) {
        emit(runInNewTab());
    }
    QWidget::mousePressEvent(event);
}


void AppIconWidget::addItemToFavorites()
{
    FavoritesCore::addToFavorites(m_item);
    sendRequestToLibrary(QString("UpdateFavorites"));
}


void AppIconWidget::editApplication()
{
    EditAppWindow *editWindow = new EditAppWindow(this, m_item);
    return editWindow->showWindow();
}


void AppIconWidget::hideApplication()
{
    m_item->setNoDisplay(true);
    m_item->saveDesktop(QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation));
}


void AppIconWidget::run()
{
    if (m_item->launch())
        sendRequestToUi(QString("Hide"));
    else
        QMessageBox::critical(this, QApplication::translate("AppLauncher", "Error"),
                              QApplication::translate("AppLauncher", "Could not run application %1").arg(m_item->exec()));
}


void AppIconWidget::runInNewTab()
{
    sendRequestToUi(QString("RunContainer"), QVariantList() << m_item->exec()
        << m_item->name());
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
                      FavoritesCore::hasApplication(m_item) ?
                      QApplication::translate("AppIconWidget", "Remove from favorites") :
                      QApplication::translate("AppIconWidget", "Add to favorites"),
                      this, SLOT(addItemToFavorites()));
    m_menu->addSeparator();

    m_menu->addAction(QApplication::translate("AppIconWidget", "Edit"),
                      this, SLOT(editApplication()));
    m_menu->addAction(QApplication::translate("AppIconWidget", "Hide"),
                      this, SLOT(hideApplication()));
}
