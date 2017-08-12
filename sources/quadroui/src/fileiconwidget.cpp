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


#include "quadroui/quadroui.h"

#include <QIcon>
#include <QKeyEvent>
#include <QMenu>

#include <quadrocore/quadro.h>


/**
 * @class FileIconWidget
 */
/**
 * @fn FileIconWidget
 */
FileIconWidget::FileIconWidget(const QFileInfo _info, const QIcon _icon,
                               const int _size, QWidget *_parent)
    : IconWidget(_size, _parent)
    , m_info(_info)
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;

    setIcon(_icon);
    setText(m_info.fileName());
    createActions();

    connect(this, SIGNAL(widgetPressed()), this, SLOT(openRequested()));
}


/**
 * @fn FileIconWidget
 */
FileIconWidget::FileIconWidget(const QString _path, const QString _icon,
                               const int _size, QWidget *_parent)
    : FileIconWidget(QFileInfo(QUrl::fromUserInput(_path).toLocalFile()),
                     QIcon::fromTheme(_icon), _size, _parent)
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;
}


/**
 * @fn ~FileIconWidget
 */
FileIconWidget::~FileIconWidget()
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;

    delete m_menu;
}


/**
 * @fn showContextMenu
 */
void FileIconWidget::showContextMenu(const QPoint &_pos)
{
    m_menu->popup(mapToGlobal(_pos));
}


/**
 * @fn keyPressEvent
 */
void FileIconWidget::keyPressEvent(QKeyEvent *_pressedKey)
{
    if (_pressedKey->key() == Qt::Key_Space)
        showProperties();

    return IconWidget::keyPressEvent(_pressedKey);
}


/**
 * @fn mousePressEvent
 */
void FileIconWidget::mousePressEvent(QMouseEvent *_event)
{
    if (_event->button() == Qt::MiddleButton) {
        emit(openInNewTabRequested());
    }

    IconWidget::mousePressEvent(_event);
}


/**
 * @fn openInNewTabRequested
 */
void FileIconWidget::openInNewTabRequested() const
{
    emit(openDirInNewTab(m_info));
}


/**
 * @fn openRequested
 */
void FileIconWidget::openRequested() const
{
    emit(openFile(m_info));
}


/**
 * @fn showProperties
 */
void FileIconWidget::showProperties()
{
    FileInfoWindow *infoWindow = new FileInfoWindow(this, m_info);

    return infoWindow->showWindow();
}


/**
 * @fn createActions
 */
void FileIconWidget::createActions()
{
    m_menu = new QMenu(this);

    m_menu->addAction(QIcon::fromTheme(m_info.isDir() ? "document-open-folder"
                                                      : "document-open"),
                      tr("Open"), this, SLOT(openRequested()));
    if (m_info.isDir())
        m_menu->addAction(QIcon::fromTheme("document-open-folder"),
                          tr("Open in new tab"), this,
                          SLOT(openInNewTabRequested()));
    m_menu->addSeparator();

    m_menu->addAction(QIcon::fromTheme("document-properties"), tr("Properties"),
                      this, SLOT(showProperties()));
}
