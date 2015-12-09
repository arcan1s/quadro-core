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


#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QLibraryInfo>
#include <QTranslator>
#include <QStandardPaths>
#include <QUrl>
#include <QWindow>

#include <quadroui/quadroui.h>

#include "settingswindow.h"
#include "quadrouiadaptor.h"
#include "version.h"


MainWindow::MainWindow(QWidget *parent, const QVariantHash args)
    : QMainWindow(parent)
{
    qSetMessagePattern(LOG_FORMAT);
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;
        for (auto metadata : getBuildData())
            qCDebug(LOG_UI) << metadata;

    setWindowIcon(QIcon(":icon"));

    ui = new Ui::MainWindow;
    ui->setupUi(this);

    // apply window properties
    setWindowFlags(Qt::CustomizeWindowHint);
    setWindowState(Qt::WindowFullScreen);

    // update configuration
    updateConfiguration(args);
}


MainWindow::~MainWindow()
{
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;

    deleteObjects();
    delete ui;
}


void MainWindow::closeEvent(QCloseEvent *event)
{
//     if ((QSystemTrayIcon::isSystemTrayAvailable()) && (configuration[QString("SYSTRAY")] == QString("true"))) {
//         hide();
//         event->ignore();
//     } else
//         closeMainWindow();
}


void MainWindow::changeTab(const int index)
{
    qCDebug(LOG_UI) << "Index" << index;
    if ((index == -1) || (index >= ui->stackedWidget->count())) return;

    return ui->stackedWidget->setCurrentIndex(index);
}


void MainWindow::closeMainWindow()
{
    qApp->quit();
}


void MainWindow::showSettingsWindow()
{
    settingsWindow->showWindow();
}


void MainWindow::updateConfiguration(const QVariantHash args)
{
    deleteObjects();
    // update configuration
    m_configPath = QStandardPaths::locate(QStandardPaths::ConfigLocation,
                                          QString("quadro.conf"));
    qCInfo(LOG_UI) << "Load configuration from" << m_configPath;
    settingsWindow = new SettingsWindow(this, m_configPath);
    if (args[QString("default")].toBool())
        settingsWindow->setDefault();
    m_configuration = settingsWindow->getSettings();
    delete settingsWindow;
    settingsWindow = nullptr;

    createObjects();
    createActions();

    show();
}


void MainWindow::createContainer(const QStringList exec, const QString name)
{
    qCDebug(LOG_UI) << "Executable" << exec;
    qCDebug(LOG_UI) << "Name" << name;

    StandaloneAppWidget *app = new StandaloneAppWidget(this, exec,
                                           ui->stackedWidget->count(), m_configuration);
    connect(app, SIGNAL(destroyWindow(const int)), this, SLOT(removeContainer(const int)));

    ui->stackedWidget->addWidget(app);
    tabActions.append(ui->toolBar->addAction(name));

    return ui->stackedWidget->setCurrentWidget(app);
}


void MainWindow::removeContainer(const int index)
{
    qCDebug(LOG_UI) << "Remove tab" << index;

    ui->stackedWidget->setCurrentIndex(0);
    QWidget *widget = ui->stackedWidget->widget(index);
    ui->stackedWidget->removeWidget(widget);
    ui->toolBar->removeAction(tabActions[index]);
    tabActions.removeAt(index);

    widget->deleteLater();
}


void MainWindow::changeTabByAction(QAction *action)
{
    return changeTab(tabActions.indexOf(action));
}


void MainWindow::clearTabs()
{
    QStringList tabs = m_configuration[QString("Tabs")].toStringList();
    disconnect(ui->toolBar, SIGNAL(actionTriggered(QAction *)),
               this, SLOT(changeTabByAction(QAction *)));

    tabActions.clear();
    ui->toolBar->clear();
    while (ui->stackedWidget->count() > 0) {
        QWidget *widget = ui->stackedWidget->widget(0);
        ui->stackedWidget->removeWidget(widget);
    }
    for (auto plugin : m_plugins) {
        int index = plugin[QString("Index")].toInt();
        QString tab = plugin[QString("Plugin")].toString();
        QString config = m_core->plugin()->configurationPath(
            QString("%1.tab-%2.conf").arg(tab).arg(tabs.indexOf(tab)));
        m_core->plugin()->unloadPlugin(index, config);
    }
}


void MainWindow::initTabs()
{
    QStringList tabs = m_configuration[QString("Tabs")].toStringList();

    for (auto tab : tabs) {
        int index = m_core->plugin()->loadPlugin(tab);
        if (index == -1) {
            qCWarning(LOG_UI) << "Could not find tab" << tab;
        } else {
            m_core->plugin()->initPlugin(index, m_configuration,
                                         QString("%1.tab-%2.conf").arg(tab).arg(tabs.indexOf(tab)));
            auto item = m_core->plugin()->plugin<TabPluginInterface>(index);
            ui->stackedWidget->addWidget(item->widget());
            tabActions.append(ui->toolBar->addAction(item->name()));
            // generate metadata
            QVariantHash metadata;
            metadata[QString("Index")] = index;
            metadata[QString("Plugin")] = tab;
        }
    }

    connect(ui->toolBar, SIGNAL(actionTriggered(QAction *)),
            this, SLOT(changeTabByAction(QAction *)));
}


void MainWindow::createActions()
{
    connect(this, SIGNAL(needToBeConfigured()), this, SLOT(showSettingsWindow()));

    // menu
    connect(ui->actionSettings, SIGNAL(triggered()), this, SLOT(showSettingsWindow()));
//     connect(ui->actionDBus_API, SIGNAL(triggered()), this, SLOT(showApi()));
//     connect(ui->actionLibrary, SIGNAL(triggered()), this, SLOT(showLibrary()));
//     connect(ui->actionReport_a_bug, SIGNAL(triggered()), this, SLOT(reportABug()));
//     connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAboutWindow()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(closeMainWindow()));
}


void MainWindow::createDBusSession()
{
    QDBusConnection bus = QDBusConnection::sessionBus();
    if (!bus.registerService(DBUS_SERVICE)) {
        qCWarning(LOG_UI) << "Could not register service";
        qCWarning(LOG_UI) << bus.lastError().message();
    }
    if (!bus.registerObject(DBUS_UI_OBJECT_PATH, new QuadroUiAdaptor(this),
                            QDBusConnection::ExportAllContents)) {
        qCWarning(LOG_UI) << "Could not register GUI object";
        qCWarning(LOG_UI) << bus.lastError().message();
    }
}


void MainWindow::createObjects()
{
    // backend
    m_core = new QuadroCore(this, m_configuration);
    createDBusSession();

    // frontend
    ui->retranslateUi(this);
    initTabs();
    settingsWindow = new SettingsWindow(this, m_configPath);
}


void MainWindow::deleteObjects()
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
