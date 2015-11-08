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

#include <language/language.h>

#include <quadroui/quadroui.h>

#include "settingswindow.h"
#include "quadrouiadaptor.h"
#include "version.h"


MainWindow::MainWindow(QWidget *parent, const QVariantHash args,
                       QTranslator *qtAppTranslator, QTranslator *appTranslator)
    : QMainWindow(parent),
      qtTranslator(qtAppTranslator),
      translator(appTranslator)
{
    qSetMessagePattern(LOG_FORMAT);
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;
        foreach (const QString metadata, getBuildData())
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
    configPath = QStandardPaths::locate(QStandardPaths::ConfigLocation,
                                        QString("quadro.conf"));
    qCInfo(LOG_UI) << "Load configuration from" << configPath;
    settingsWindow = new SettingsWindow(this, configPath);
    if (args[QString("default")].toBool())
        settingsWindow->setDefault();
    configuration = settingsWindow->getSettings();
    delete settingsWindow;
    settingsWindow = nullptr;

    // update translation
    qApp->removeTranslator(translator);
    QString language = Language::defineLanguage(configPath, args[QString("options")].toString());
    qCInfo(LOG_UI) << "Language is" << language;
    qtTranslator->load(QString("qt_%1").arg(language), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    qApp->installTranslator(qtTranslator);
    translator->load(QString(":/translations/%1").arg(language));
    qApp->installTranslator(translator);

    createObjects();
    createActions();

    show();
}


void MainWindow::createContainer(const QStringList exec, const QString name)
{
    qCDebug(LOG_UI) << "Executable" << exec;
    qCDebug(LOG_UI) << "Name" << name;

    StandaloneAppWidget *app = new StandaloneAppWidget(this, exec,
                                           ui->stackedWidget->count(), configuration);
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
    disconnect(ui->toolBar, SIGNAL(actionTriggered(QAction *)),
               this, SLOT(changeTabByAction(QAction *)));

    tabActions.clear();
    ui->toolBar->clear();
    while (ui->stackedWidget->count() > 0) {
        QWidget *widget = ui->stackedWidget->widget(0);
        ui->stackedWidget->removeWidget(widget);
        widget->deleteLater();
    }
}


void MainWindow::initTabs()
{
    QStringList tabs = configuration[QString("Tabs")].toStringList();
    foreach (const QString tab, tabs) {
        TabPluginInterface *item = m_core->plugin()->tabPlugin(tab);
        if (item == nullptr) {
            qCWarning(LOG_UI) << "Could not find tab" << tab;
        } else {
            item->setArgs(m_core, configuration);
            item->init();
            ui->stackedWidget->addWidget(item->widget());
            tabActions.append(ui->toolBar->addAction(item->name()));
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
    m_core = new QuadroCore(this, configuration);
    createDBusSession();

    // frontend
    ui->retranslateUi(this);
    initTabs();
    settingsWindow = new SettingsWindow(this, configPath);
}


void MainWindow::deleteObjects()
{
    // backend
    delete m_core;
    m_core = nullptr;

    // frontend
    delete settingsWindow;
    settingsWindow = nullptr;
    clearTabs();

    QDBusConnection::sessionBus().unregisterObject(DBUS_UI_OBJECT_PATH);
    QDBusConnection::sessionBus().unregisterService(DBUS_SERVICE);
}
