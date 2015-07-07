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
#include <QDebug>
#include <QLibraryInfo>
#include <QTranslator>
#include <QUrl>

#include <language/language.h>
#include <pdebug/pdebug.h>

#include "settingswindow.h"
#include "version.h"


MainWindow::MainWindow(QWidget *parent, const QVariantMap args,
                       QTranslator *qtAppTranslator, QTranslator *appTranslator)
    : QMainWindow(parent),
      configPath(args[QString("config")].toString()),
      debug(args[QString("debug")].toBool()),
      qtTranslator(qtAppTranslator),
      translator(appTranslator)
{
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
    if (debug) qDebug() << PDEBUG;

    deleteObjects();
    delete ui;
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if (debug) qDebug() << PDEBUG;

//     if ((QSystemTrayIcon::isSystemTrayAvailable()) && (configuration[QString("SYSTRAY")] == QString("true"))) {
//         hide();
//         event->ignore();
//     } else
//         closeMainWindow();
}


void MainWindow::changeTab(const int number)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << "Index" << number;
    if ((number == -1) || (number >= ui->stackedWidget->count())) return;

    return ui->stackedWidget->setCurrentIndex(number);
}


void MainWindow::closeMainWindow()
{
    if (debug) qDebug() << PDEBUG;

    qApp->quit();
}


void MainWindow::showSettingsWindow()
{
    if (debug) qDebug() << PDEBUG;

    settingsWindow->showWindow();
}


void MainWindow::updateConfiguration(const QVariantMap args)
{
    if (debug) qDebug() << PDEBUG;

    deleteObjects();
    // update configuration
    QString actualConfigPath = QFile(configPath).exists() ? configPath : QString("/etc/netctl-gui.conf");
    settingsWindow = new SettingsWindow(this, debug, actualConfigPath);
    if (args[QString("default")].toBool())
        settingsWindow->setDefault();
    configuration = settingsWindow->getSettings();
    delete settingsWindow;

    // update translation
    qApp->removeTranslator(translator);
    QString language = Language::defineLanguage(actualConfigPath, args[QString("options")].toString());
    if (debug) qDebug() << PDEBUG << ":" << "Language is" << language;
    qtTranslator->load(QString("qt_%1").arg(language), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    qApp->installTranslator(qtTranslator);
    translator->load(QString(":/translations/%1").arg(language));
    qApp->installTranslator(translator);

    createObjects();
    createActions();

    show();
}


void MainWindow::changeTabByAction(QAction *action)
{
    if (debug) qDebug() << PDEBUG;

    QWidget *actionWidget = ui->toolBar->widgetForAction(action);

    return ui->stackedWidget->setCurrentWidget(actionWidget);
}


void MainWindow::clearTabs()
{
    if (debug) qDebug() << PDEBUG;

    disconnect(ui->toolBar, SIGNAL(actionTriggered(QAction *)),
               this, SLOT(changeTabByAction(QAction *)));

    ui->toolBar->clear();
    while (ui->stackedWidget->count() > 0) {
        QWidget *widget = ui->stackedWidget->widget(0);
        ui->stackedWidget->removeWidget(widget);
        widget->deleteLater();
    }
}


void MainWindow::initTabs()
{
    if (debug) qDebug() << PDEBUG;

    QStringList tabs = configuration[QString("Tabs")].toStringList();
    for (int i=0; i<tabs.count(); i++) {
        if (tabs[i] == QString("applauncher")) {
        } else if (tabs[i] == QString("favorites")) {
        } else if (tabs[i] == QString("filemanager")) {
        } else continue;
//         ui->stackedWidget->addWidget(widget init);
        ui->toolBar->addWidget(ui->stackedWidget->widget(ui->stackedWidget->count() - 1));
    }

    connect(ui->toolBar, SIGNAL(actionTriggered(QAction *)),
            this, SLOT(changeTabByAction(QAction *)));
}


void MainWindow::createActions()
{
    if (debug) qDebug() << PDEBUG;

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
    if (debug) qDebug() << PDEBUG;

    QDBusConnection bus = QDBusConnection::sessionBus();
    if (!bus.registerService(DBUS_SERVICE)) {
        if (debug) qDebug() << PDEBUG << ":" << "Could not register service";
        if (debug) qDebug() << PDEBUG << ":" << bus.lastError().message();
    }
//     if (!bus.registerObject(DBUS_OBJECT_PATH,
//                             new QuadroUiAdaptor(this),
//                             QDBusConnection::ExportAllContents)) {
//         if (debug) qDebug() << PDEBUG << ":" << "Could not register GUI object";
//         if (debug) qDebug() << PDEBUG << ":" << bus.lastError().message();
//     }
}


void MainWindow::createObjects()
{
    if (debug) qDebug() << PDEBUG;

    ui->retranslateUi(this);
    settingsWindow = new SettingsWindow(this, debug, configPath);
}


void MainWindow::deleteObjects()
{
    if (debug) qDebug() << PDEBUG;

    if (settingsWindow != nullptr) delete settingsWindow;

    clearTabs();
}
