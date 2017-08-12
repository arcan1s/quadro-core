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


#include "QuadroMainWindow.h"
#include "ui_QuadroMainWindow.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QLibraryInfo>
#include <QStandardPaths>
#include <QTranslator>
#include <QUrl>
#include <QWindow>

#include <quadrocore/Quadro.h>
#include <quadroui/QuadroUi.h>

#include "QuadroUiAdaptor.h"
#include "SettingsWindow.h"

using namespace Quadro;


QuadroMainWindow::QuadroMainWindow(QWidget *_parent, const QVariantHash _args)
    : QMainWindow(_parent)
{
    QuadroDebug::applyLogFormat();
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;
    for (auto &metadata : QuadroDebug::getBuildData())
        qCDebug(LOG_UI) << metadata;

    setWindowIcon(QIcon(":icon"));

    ui = new Ui::QuadroMainWindow;
    ui->setupUi(this);

    // apply window properties
    setWindowFlags(Qt::CustomizeWindowHint);
    setWindowState(Qt::WindowFullScreen);

    // update configuration
    updateConfiguration(_args);
}


QuadroMainWindow::~QuadroMainWindow()
{
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;

    deleteObjects();
    delete ui;
}


void QuadroMainWindow::closeEvent(QCloseEvent *_event)
{
    //     if ((QSystemTrayIcon::isSystemTrayAvailable()) &&
    //     (configuration["SYSTRAY"] == "true")) {
    //         hide();
    //         event->ignore();
    //     } else
    //         closeMainWindow();
}


void QuadroMainWindow::changeTab(const int _index)
{
    qCDebug(LOG_UI) << "Index" << _index;
    if ((_index == -1) || (_index >= ui->stackedWidget->count()))
        return;

    return ui->stackedWidget->setCurrentIndex(_index);
}


void QuadroMainWindow::closeMainWindow()
{
    qApp->quit();
}


void QuadroMainWindow::showSettingsWindow()
{
    settingsWindow->showWindow();
}


void QuadroMainWindow::updateConfiguration(const QVariantHash &_args)
{
    deleteObjects();
    // update configuration
    m_configPath
        = QStandardPaths::locate(QStandardPaths::ConfigLocation, "quadro.conf");
    qCInfo(LOG_UI) << "Load configuration from" << m_configPath;
    settingsWindow = new SettingsWindow(this, m_configPath);
    if (_args["default"].toBool())
        settingsWindow->setDefault();
    m_configuration = settingsWindow->getSettings();
    delete settingsWindow;
    settingsWindow = nullptr;

    createObjects();
    createActions();

    show();
}


void QuadroMainWindow::createContainer(const QStringList &_exec,
                                       const QString &_name)
{
    qCDebug(LOG_UI) << "Executable" << _exec << "name" << _name;

    StandaloneAppWidget *app
        = new StandaloneAppWidget(this, _exec, ui->stackedWidget->count());
    connect(app, SIGNAL(destroyWindow(const int)), this,
            SLOT(removeContainer(const int)));

    ui->stackedWidget->addWidget(app);
    tabActions.append(ui->toolBar->addAction(_name));

    return ui->stackedWidget->setCurrentWidget(app);
}


void QuadroMainWindow::createWebContainer(const QString &_url,
                                          const bool _showOpen)
{
    qCDebug(LOG_UI) << "Create URL" << _url << "with show open button"
                    << _showOpen;

    WebAppWidget *app
        = new WebAppWidget(this, ui->stackedWidget->count(), _showOpen);
    connect(app, SIGNAL(destroyWindow(const int)), this,
            SLOT(removeContainer(const int)));
    connect(app, &WebAppWidget::updateTitle,
            [this](const int index, const QString title) {
                tabActions[index]->setText(title);
            });

    ui->stackedWidget->addWidget(app);
    tabActions.append(ui->toolBar->addAction("about:blank"));
    app->loadUrl(QUrl::fromUserInput(_url));

    return ui->stackedWidget->setCurrentWidget(app);
}


void QuadroMainWindow::removeContainer(const int _index)
{
    qCDebug(LOG_UI) << "Remove tab" << _index;

    ui->stackedWidget->setCurrentIndex(0);
    QWidget *widget = ui->stackedWidget->widget(_index);
    ui->stackedWidget->removeWidget(widget);
    ui->toolBar->removeAction(tabActions[_index]);
    tabActions.removeAt(_index);

    widget->deleteLater();
}


void QuadroMainWindow::changeTabByAction(QAction *_action)
{
    return changeTab(tabActions.indexOf(_action));
}


void QuadroMainWindow::clearTabs()
{
    QStringList tabs = m_configuration["Tabs"].toStringList();
    disconnect(ui->toolBar, SIGNAL(actionTriggered(QAction *)), this,
               SLOT(changeTabByAction(QAction *)));

    tabActions.clear();
    ui->toolBar->clear();
    while (ui->stackedWidget->count() > 0) {
        QWidget *widget = ui->stackedWidget->widget(0);
        ui->stackedWidget->removeWidget(widget);
    }
    for (auto &plugin : m_plugins) {
        int index = plugin["Index"].toInt();
        QString tab = plugin["Plugin"].toString();
        m_core->plugin()->unloadPlugin(
            index, QString("%1.tab-%2.conf").arg(tab).arg(tabs.indexOf(tab)));
    }
}


void QuadroMainWindow::initTabs()
{
    QStringList tabs = m_configuration["Tabs"].toStringList();

    for (auto &tab : tabs) {
        int index = m_core->plugin()->loadPlugin(tab);
        if (index == -1) {
            qCWarning(LOG_UI) << "Could not find tab" << tab;
        } else {
            m_core->plugin()->initPlugin(
                index,
                QString("%1.tab-%2.conf").arg(tab).arg(tabs.indexOf(tab)));
            auto item = m_core->plugin()->plugin<TabPluginInterface>(index);
            ui->stackedWidget->addWidget(item->widget());
            tabActions.append(ui->toolBar->addAction(item->name()));
            // generate metadata
            QVariantHash metadata;
            metadata["Index"] = index;
            metadata["Plugin"] = tab;
            m_plugins.append(metadata);
        }
    }

    connect(ui->toolBar, SIGNAL(actionTriggered(QAction *)), this,
            SLOT(changeTabByAction(QAction *)));
}


void QuadroMainWindow::createActions()
{
    connect(this, SIGNAL(needToBeConfigured()), this,
            SLOT(showSettingsWindow()));

    // menu
    connect(ui->actionSettings, SIGNAL(triggered()), this,
            SLOT(showSettingsWindow()));
    //     connect(ui->actionDBus_API, SIGNAL(triggered()), this,
    //     SLOT(showApi()));
    //     connect(ui->actionLibrary, SIGNAL(triggered()), this,
    //     SLOT(showLibrary()));
    //     connect(ui->actionReport_a_bug, SIGNAL(triggered()), this,
    //     SLOT(reportABug()));
    //     connect(ui->actionAbout, SIGNAL(triggered()), this,
    //     SLOT(showAboutWindow()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(closeMainWindow()));
}


void QuadroMainWindow::createDBusSession()
{
    QDBusConnection bus = QDBusConnection::sessionBus();
    if (!bus.registerService(DBUS_SERVICE)) {
        qCWarning(LOG_UI) << "Could not register service"
                          << bus.lastError().message();
    } else if (!bus.registerObject(DBUS_UI_OBJECT_PATH,
                                   new QuadroUiAdaptor(this),
                                   QDBusConnection::ExportAllContents)) {
        qCWarning(LOG_UI) << "Could not register GUI object"
                          << bus.lastError().message();
    }
}


void QuadroMainWindow::createObjects()
{
    // backend
    m_core = new QuadroCore(this);
    createDBusSession();

    // frontend
    initTabs();
    ui->retranslateUi(this);
    settingsWindow = new SettingsWindow(this, m_configPath);
}


void QuadroMainWindow::deleteObjects()
{
    // frontend
    delete settingsWindow;
    settingsWindow = nullptr;
    clearTabs();

    // backend
    delete m_core;
    m_core = nullptr;

    QDBusConnection::sessionBus().unregisterObject(DBUS_UI_OBJECT_PATH);
    QDBusConnection::sessionBus().unregisterService(DBUS_SERVICE);
}
