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
#include <QUrl>

#include <language/language.h>

#include "applauncherwidget.h"
#include "settingswindow.h"
#include "version.h"


MainWindow::MainWindow(QWidget *parent, const QVariantMap args,
                       QTranslator *qtAppTranslator, QTranslator *appTranslator)
    : QMainWindow(parent),
      configPath(args[QString("config")].toString()),
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


void MainWindow::updateConfiguration(const QVariantMap args)
{
    deleteObjects();
    // update configuration
    QString actualConfigPath = QFile(configPath).exists() ? configPath : QString("/etc/quadro.conf");
    settingsWindow = new SettingsWindow(this, actualConfigPath);
    if (args[QString("default")].toBool())
        settingsWindow->setDefault();
    configuration = settingsWindow->getSettings();
    delete settingsWindow;

    // update translation
    qApp->removeTranslator(translator);
    QString language = Language::defineLanguage(actualConfigPath, args[QString("options")].toString());
    qCInfo(LOG_UI) << "Language is" << language;
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
    int index = -1;
    for (int i=0; i<tabActions.count(); i++) {
        if (tabActions[i] != action) continue;
        index = i;
        break;
    }

    return changeTab(index);
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
    for (int i=0; i<tabs.count(); i++) {
        if (tabs[i] == QString("applauncher")) {
            ui->stackedWidget->addWidget(new AppLauncher(this, launcher, recent,
                                                         configuration));
        } else if (tabs[i] == QString("favorites")) {
            ui->stackedWidget->addWidget(new QWidget());
        } else if (tabs[i] == QString("filemanager")) {
            ui->stackedWidget->addWidget(new QWidget());
        } else continue;
        tabActions.append(ui->toolBar->addAction(tabs[i]));
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
//     if (!bus.registerObject(DBUS_OBJECT_PATH,
//                             new QuadroUiAdaptor(this),
//                             QDBusConnection::ExportAllContents)) {
//         if (debug) qDebug() << PDEBUG << ":" << "Could not register GUI object";
//         if (debug) qDebug() << PDEBUG << ":" << bus.lastError().message();
//     }
}


void MainWindow::createObjects()
{
    // backend
    launcher = new LauncherCore(this);
    launcher->initApplications();
    recent = new RecentlyCore(this);
    recent->initApplications();

    // frontend
    ui->retranslateUi(this);
    initTabs();
    settingsWindow = new SettingsWindow(this, configPath);
}


void MainWindow::deleteObjects()
{
    // frontend
    if (settingsWindow != nullptr) delete settingsWindow;
    clearTabs();

    // backend
    if (launcher != nullptr) delete launcher;
    if (recent != nullptr) delete recent;

}
