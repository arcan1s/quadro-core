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
 * @file applicationitem.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */
#include <qtextstream.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QDebug>

#include <language/language.h>
#include <pdebug/pdebug.h>

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
    updateConfiguration(args);
}


MainWindow::~MainWindow()
{
    if (debug) qDebug() << PDEBUG;

    deleteObjects();
    delete ui;
}


void MainWindow::updateConfiguration(const QVariantMap args)
{
    if (debug) qDebug() << PDEBUG;

    deleteObjects();
}


void MainWindow::createActions()
{
    if (debug) qDebug() << PDEBUG;
}


void MainWindow::createDBusSession()
{
    if (debug) qDebug() << PDEBUG;

    QDBusConnection bus = QDBusConnection::sessionBus();
    if (!bus.registerService(DBUS_SERVICE)) {
        if (debug) qDebug() << PDEBUG << ":" << "Could not register service";
        if (debug) qDebug() << PDEBUG << ":" << bus.lastError().message();
    }
    if (!bus.registerObject(DBUS_OBJECT_PATH,
                            new NetctlGuiAdaptor(this),
                            QDBusConnection::ExportAllContents)) {
        if (debug) qDebug() << PDEBUG << ":" << "Could not register GUI object";
        if (debug) qDebug() << PDEBUG << ":" << bus.lastError().message();
    }
}


void MainWindow::createObjects()
{
    if (debug) qDebug() << PDEBUG;
}


void MainWindow::deleteObjects()
{
    if (debug) qDebug() << PDEBUG;
}
