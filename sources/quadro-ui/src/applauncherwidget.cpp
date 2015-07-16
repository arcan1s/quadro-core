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


#include "applauncherwidget.h"
#include "ui_applauncherwidget.h"

#include <QDebug>
#include <QIcon>
#include <QLabel>
#include <QScrollArea>

#include <flowlayout/flowlayout.h>
#include <pdebug/pdebug.h>

#include "iconwidget.h"


AppLauncher::AppLauncher(QWidget *parent, LauncherCore *appLauncher,
                         const QVariantMap settings, const bool debugCmd)
    : QMainWindow(parent),
      debug(debugCmd),
      launcher(appLauncher),
      configuration(settings)
{
    ui = new Ui::AppLauncher;
    ui->setupUi(this);

    createObjects();
    createActions();
}


AppLauncher::~AppLauncher()
{
    if (debug) qDebug() << PDEBUG;

    deleteObjects();
    delete ui;
}


QSize AppLauncher::itemSize()
{
    if (debug) qDebug() << PDEBUG;

    return QSize(configuration[QString("GridSize")].toFloat(),
                 configuration[QString("GridSize")].toFloat());
}


void AppLauncher::changeCategory(const int index)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << "Index" << index;
    if ((index == -1) || (index >= ui->stackedWidget->count())) return;

    return ui->stackedWidget->setCurrentIndex(index);
}


void AppLauncher::changeCategoryByAction(QAction *action)
{
    if (debug) qDebug() << PDEBUG;

    int index = -1;
    for (int i=0; i<categoryButtons.count(); i++) {
        if (categoryButtons[i] != action) continue;
        index = i;
        break;
    }

    return changeCategory(index);
}


void AppLauncher::runApplication()
{
    if (debug) qDebug() << PDEBUG;

    // TODO implement mainwindow hidding (DBus?)
}


void AppLauncher::showSearchResults(const QString search)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << "Search substring" << search;

    // clear
    QLayoutItem *item;
    while ((item = categoryWidgets.last()->layout()->takeAt(0))) {
        delete item->widget();
        delete item;
    }

    // return if none to do here
    if (search.isEmpty()) return ui->stackedWidget->setCurrentIndex(0);
    // add items
    QMap<QString, ApplicationItem *> apps = launcher->applicationsBySubstr(search);
    for (int i=0; i<apps.keys().count(); i++) {
        QWidget *item = new IconWidget(apps[apps.keys()[i]], itemSize(),
                                       categoryWidgets.last(), debug);
        categoryWidgets.last()->layout()->addWidget(item);
        connect(item, SIGNAL(widgetPressed()), this, SLOT(runApplication()));
    }

    return ui->stackedWidget->setCurrentIndex(ui->stackedWidget->count() - 1);
}


void AppLauncher::createActions()
{
    if (debug) qDebug() << PDEBUG;
}


void AppLauncher::createObjects()
{
    if (debug) qDebug() << PDEBUG;

    QStringList categories = launcher->availableCategories();
    for (int i=0; i<categories.count(); i++) {
        // backend
        categoryButtons.append(ui->toolBar->addAction(categories[i]));
        // frontend
        // scroll area
        QScrollArea *area = new QScrollArea(this);
        area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        area->setWidgetResizable(true);
        ui->stackedWidget->addWidget(area);
        // widget
        categoryWidgets.append(new QWidget(area));
        categoryWidgets[i]->setLayout(new FlowLayout(categoryWidgets[i]));
        initCategory(categories[i], categoryWidgets[i]);
        area->setWidget(categoryWidgets[i]);
    }

    // search widget
    QScrollArea *area = new QScrollArea(this);
    area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    area->setWidgetResizable(true);
    ui->stackedWidget->addWidget(area);
    categoryWidgets.append(new QWidget(area));
    categoryWidgets.last()->setLayout(new FlowLayout(categoryWidgets.last()));
    area->setWidget(categoryWidgets.last());

    connect(ui->toolBar, SIGNAL(actionTriggered(QAction *)),
            this, SLOT(changeCategoryByAction(QAction *)));
    connect(ui->lineEdit, SIGNAL(textEdited(QString)),
            this, SLOT(showSearchResults(QString)));
}


void AppLauncher::deleteObjects()
{
    if (debug) qDebug() << PDEBUG;

    categoryButtons.clear();
    categoryWidgets.clear();
}


void AppLauncher::initCategory(const QString category, QWidget *widget)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << "Category" << category;

    QMap<QString, ApplicationItem *> apps = launcher->applicationsByCategory(category);
    for (int i=0; i<apps.keys().count(); i++) {
        QWidget *item = new IconWidget(apps[apps.keys()[i]], itemSize(), widget, debug);
        widget->layout()->addWidget(item);
        connect(item, SIGNAL(widgetPressed()), this, SLOT(runApplication()));
    }
}
