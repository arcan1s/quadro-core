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
 * @file webappwidget.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadroui/quadroui.h"
#include "ui_webappwidget.h"

#include <QInputDialog>
#include <QStandardPaths>
#include <QWebEngineHistory>
#include <QWebEngineProfile>
#include <QWebEngineView>

#include <quadrocore/quadro.h>


/**
 * @class WebAppWidget
 */
/**
 * @fn WebAppWidget
 */
WebAppWidget::WebAppWidget(QWidget *_parent, const int _index,
                           const bool _showOpen)
    : QMainWindow(_parent)
    , m_index(_index)
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;

    ui = new Ui::WebAppWidget;
    ui->setupUi(this);

    // apply show open settings
    ui->actionOpen->setEnabled(_showOpen);
    ui->actionOpen->setVisible(_showOpen);
    // apply show close settings
    ui->actionClose->setEnabled(_index != -1);
    ui->actionClose->setVisible(_index != -1);

    createActions();
}


/**
 * @fn ~WebAppWidget
 */
WebAppWidget::~WebAppWidget()
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;

    delete ui;
}


/**
 * @fn state
 */
WebPageState WebAppWidget::state() const
{
    return m_state;
}


/**
 * @fn url
 */
QString WebAppWidget::url() const
{
    return ui->webView->url().toDisplayString();
}


/**
 * @fn loadUrl
 */
void WebAppWidget::loadUrl(const QUrl &_url)
{
    qCDebug(LOG_UILIB) << "Loading url" << _url.toDisplayString();

    ui->webView->load(_url);
}


/**
 * @fn setCache
 */
void WebAppWidget::setCache(const QString &_dirName)
{
    qCDebug(LOG_UILIB) << "Set cache directory to" << _dirName;

    QString dirPath = QString("%1/quadro-%2")
                          .arg(QStandardPaths::writableLocation(
                              QStandardPaths::GenericCacheLocation))
                          .arg(_dirName);
    qCInfo(LOG_UILIB) << "Full cache directory path" << dirPath;

    ui->webView->page()->profile()->setCachePath(dirPath);
}


/**
 * @fn changePageState
 */
void WebAppWidget::changePageState()
{
    if ((m_state == WebPageState::Loaded)
        || (m_state == WebPageState::Failed)) {
        ui->webView->reload();
    } else if (m_state == WebPageState::Started) {
        ui->webView->stop();
    }
}


/**
 * @fn getNewUrl
 */
void WebAppWidget::getNewUrl()
{
    QString url = QInputDialog::getText(this, tr("New URL"), tr("URL"));

    if (!url.isEmpty())
        loadUrl(QUrl::fromUserInput(url));
    else
        qCInfo(LOG_UILIB) << "No url specified";
}


/**
 * @fn updatePageState
 */
void WebAppWidget::updatePageState(const WebPageState _state)
{
    qCDebug(LOG_UILIB) << "Current page state" << static_cast<int>(_state);

    m_state = _state;

    // apply ui changes
    // refresh action
    if (_state == WebPageState::Started)
        ui->actionRefresh->setIcon(QIcon::fromTheme("process-stop"));
    else
        ui->actionRefresh->setIcon(QIcon::fromTheme("view-refresh"));
    // back and forward actions
    if (_state == WebPageState::Loaded) {
        ui->actionBack->setEnabled(ui->webView->history()->canGoBack());
        ui->actionForward->setEnabled(ui->webView->history()->canGoForward());
    }
}


/**
 * @fn createActions
 */
void WebAppWidget::createActions()
{
    // tool actions
    connect(ui->actionBack, SIGNAL(triggered()), ui->webView, SLOT(back()));
    connect(ui->actionClose, &QAction::triggered, [this](const bool) {
        if (m_index != -1)
            emit(destroyWindow(m_index));
    });
    connect(ui->actionForward, SIGNAL(triggered()), ui->webView,
            SLOT(forward()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(getNewUrl()));
    connect(ui->actionRefresh, SIGNAL(triggered()), this,
            SLOT(changePageState()));

    // webview actions
    connect(ui->webView, &QWebEngineView::loadFinished, [this](
                                                            const bool state) {
        updatePageState(state ? WebPageState::Loaded : WebPageState::Failed);
    });
    connect(ui->webView, &QWebEngineView::loadStarted,
            [this]() { updatePageState(WebPageState::Started); });
}
