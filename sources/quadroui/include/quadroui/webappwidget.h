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
 * @file webappwidget.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef WEBAPPWIDGET_H
#define WEBAPPWIDGET_H

#include <QMainWindow>


/**
 * @enum WebPageState
 * @brief available web page states
 * @var WebPageState::None
 * type is not defined
 * @var WebPageState::Loaded
 * page is loaded
 * @var WebPageState::Started
 * page loading is started
 * @var WebPageState::Failed
 * web page loading failed
 */
enum class WebPageState { None = 0, Loaded, Started, Failed };

namespace Ui
{
class WebAppWidget;
}

/**
 * @brief The WebAppWidget class provides widget with generic web actions
 */
class WebAppWidget : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(WebPageState state READ state)
    Q_PROPERTY(QString url READ url)

public:
    /**
     * @brief WebAppWidget class constructor
     * @param _parent pointer to parent object
     * @param _index tab index
     * @param _showOpen show open URL action
     */
    explicit WebAppWidget(QWidget *_parent, const int _index = -1,
                          const bool _showOpen = true);
    /**
     * @brief WebAppWidget class destructor
     */
    virtual ~WebAppWidget();
    /**
     * @brief current web page state
     * @return enum value from current state
     */
    WebPageState state() const;
    /**
     * @brief current URL
     * @return current URL as string
     */
    QString url() const;

public slots:
    /**
     * @brief method which will be called to load URL
     * @param _url URL string
     */
    void loadUrl(const QUrl &_url);
    /**
     * @brief method which will be called to save cache to local drive
     * @param _dirName cache directory name
     */
    void setCache(const QString &_dirName);

signals:
    /**
     * @brief signal which will be emitted when all windows will be closed
     * @param _index tab index
     */
    void destroyWindow(const int _index);
    /**
     * @brief signal which will be emitted when update tab title will be
     * requested
     * @param _index tab index
     * @param _title new tab title
     */
    void updateTitle(const int _index, const QString &_title);

private slots:
    /**
     * @brief method which automatically select should be page updated or
     * stopped and call related method
     */
    void changePageState();
    /**
     * @brief method which will be called on requesting url changing
     */
    void getNewUrl();
    /**
     * @brief method which connects to QWebView signals
     * @param _state web page state
     */
    void updatePageState(const WebPageState _state);

private:
    // ui
    /**
     * @brief pointer to UI object
     */
    Ui::WebAppWidget *ui = nullptr;
    // backend
    /**
     * @brief additional method to create window actions
     */
    void createActions();
    // configuration
    /**
     * @brief tab index
     */
    int m_index;
    /**
     * @brief current web page state
     */
    WebPageState m_state = WebPageState::None;
};


#endif /* STANDALONEAPPWIDGET_H */
