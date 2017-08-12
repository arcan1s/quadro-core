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
 * @file AppIconWidget.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadroui/QuadroUi.h"

#include <QFileDialog>
#include <QInputDialog>
#include <QMenu>
#include <QMessageBox>
#include <QMouseEvent>
#include <QStandardPaths>

#include <quadrocore/Quadro.h>

using namespace Quadro;


/**
 * @class AppIconWidget
 */
/**
 * @fn AppIconWidget
 */
AppIconWidget::AppIconWidget(ApplicationItem *_appItem, const int _size,
                             QWidget *_parent)
    : IconWidget(_size, _parent)
    , m_item(_appItem)
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;

    setIcon(m_item->appIcon());
    setText(m_item->name());
    QStringList tooltip;
    if (!m_item->genericName().isEmpty())
        tooltip.append(m_item->genericName());
    if (!m_item->comment().isEmpty())
        tooltip.append(m_item->comment());
    setToolTip(tooltip.join('\n'));
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

    IconWidget::mousePressEvent(_event);
}


/**
 * @fn addItemToFavorites
 */
void AppIconWidget::addItemToFavorites()
{
    FavoritesCore::addToFavorites(m_item);
    DBusOperations::sendRequestToLibrary("UpdateFavorites");
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
    m_item->saveDesktop(
        QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation));
    DBusOperations::sendRequestToLibrary("UpdateApplications");
}


/**
 * @fn run
 */
void AppIconWidget::run()
{
    if (m_item->launch(m_args))
        emit(applicationIsRunning());
    else
        QMessageBox::critical(
            this, tr("Error"), tr("Error"),
            tr("Could not run application %1").arg(m_item->exec()));
}


/**
 * @fn runInNewTab
 */
void AppIconWidget::runInNewTab()
{
    emit(standaloneApplicationRequested(m_item->generateExec(m_args),
                                        m_item->name()));
}


/**
 * @fn setFiles
 */
void AppIconWidget::setFiles()
{
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Select files"));
    if (files.isEmpty())
        return;

    m_args.clear();
    QStringList argsFiles;
    QStringList argsUrls;

    for (auto &file : files) {
        m_args["%f"] = file;
        argsFiles.append(file);
        m_args["%u"] = QString("file://%1").arg(file);
        argsUrls.append(QString("file://%1").arg(file));
    }
    m_args["%F"] = argsFiles;
    m_args["%U"] = argsUrls;
}


/**
 * @fn setUrls
 */
void AppIconWidget::setUrls()
{
    QStringList urls
        = QInputDialog::getMultiLineText(this, tr("Select URLs"), tr("URLs"))
              .split('\n');
    if (urls.isEmpty())
        return;

    m_args.clear();
    QStringList argsUrls;

    for (auto &url : urls) {
        m_args["%u"] = url;
        argsUrls.append(url);
    }
    m_args["%U"] = argsUrls;
}


/**
 * @fn createActions
 */
void AppIconWidget::createActions()
{
    bool isFavorites = DBusOperations::sendRequestToLibrary("Favorites")
                           .at(0)
                           .toStringList()
                           .contains(m_item->name());
    m_menu = new QMenu(this);

    m_menu->addAction(QIcon::fromTheme("system-run"), tr("Run application"),
                      this, SLOT(run()));
    m_menu->addAction(QIcon::fromTheme("system-run"),
                      tr("Run application in new tab"), this,
                      SLOT(runInNewTab()));
    m_menu->addAction(QIcon::fromTheme("emblem-favorites"),
                      isFavorites ? tr("Remove from favorites")
                                  : tr("Add to favorites"),
                      this, SLOT(addItemToFavorites()));
    m_menu->addSeparator();

    m_menu->addAction(tr("Select files"), this, SLOT(setFiles()));
    m_menu->addAction(tr("Select URLs"), this, SLOT(setUrls()));
    m_menu->addSeparator();

    m_menu->addAction(tr("Edit"), this, SLOT(editApplication()));
    m_menu->addAction(tr("Hide"), this, SLOT(hideApplication()));
}
