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

#include <QIcon>
#include <QLabel>
#include <QScrollArea>

#include <flowlayout/flowlayout.h>

#include "iconwidget.h"
#include "quadro/quadrodebug.h"


AppLauncher::AppLauncher(QWidget *parent, LauncherCore *appLauncher,
                         RecentlyCore *recentLauncher, const QVariantHash settings)
    : QMainWindow(parent),
      launcher(appLauncher),
      recent(recentLauncher),
      configuration(settings)
{
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;

    ui = new Ui::AppLauncher;
    ui->setupUi(this);

    createObjects();
    createActions();
}


AppLauncher::~AppLauncher()
{
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;

    deleteObjects();
    delete ui;
}


QSize AppLauncher::itemSize()
{
    return QSize(configuration[QString("GridSize")].toFloat(),
                 configuration[QString("GridSize")].toFloat());
}


void AppLauncher::changeCategory(const int index)
{
    qCDebug(LOG_UI) << "Index" << index;
    if ((index == -1) || (index >= ui->stackedWidget->count())) return;

    return ui->stackedWidget->setCurrentIndex(index);
}


void AppLauncher::changeCategoryByAction(QAction *action)
{
    int index = -1;
    for (int i=0; i<categoryButtons.count(); i++) {
        if (categoryButtons.at(i) != action) continue;
        index = i;
        break;
    }

    return changeCategory(index);
}


void AppLauncher::runApplication()
{
    // TODO implement mainwindow hidding (DBus?)
}


void AppLauncher::runCustomApplication()
{
    QString exec = ui->lineEdit->text();
    ApplicationItem *item = recent->addItemByName(exec);

    // TODO error checking
    item->launch();
}


void AppLauncher::showSearchResults(const QString search)
{
    qCDebug(LOG_UI) << "Search substring" << search;

    // clear
    QLayoutItem *item;
    while ((item = categoryWidgets.last()->layout()->takeAt(0))) {
        delete item->widget();
        delete item;
    }

    // return if none to do here
    if (search.isEmpty()) return ui->stackedWidget->setCurrentIndex(0);
    // add items
    QMap<QString, ApplicationItem *> apps = recent->applicationsBySubstr(search);
    QMap<QString, ApplicationItem *> launcherApps = launcher->applicationsBySubstr(search);
    foreach (ApplicationItem *app, apps.values() + launcherApps.values()) {
        QWidget *wItem = new IconWidget(app, itemSize(), categoryWidgets.last());
        categoryWidgets.last()->layout()->addWidget(wItem);
        connect(wItem, SIGNAL(widgetPressed()), this, SLOT(runApplication()));
    }

    return ui->stackedWidget->setCurrentIndex(ui->stackedWidget->count() - 1);
}


void AppLauncher::createActions()
{
    // TODO
}


void AppLauncher::createObjects()
{
    QStringList categories = launcher->availableCategories();
    foreach (const QString cat, categories) {
        // backend
        categoryButtons.append(ui->toolBar->addAction(cat));
        // frontend
        // scroll area
        QScrollArea *area = new QScrollArea(this);
        area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        area->setWidgetResizable(true);
        ui->stackedWidget->addWidget(area);
        // widget
        categoryWidgets.append(new QWidget(area));
        categoryWidgets.last()->setLayout(new FlowLayout(categoryWidgets.last()));
        initCategory(cat, categoryWidgets.last());
        area->setWidget(categoryWidgets.last());
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
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(runCustomApplication()));
    connect(ui->lineEdit, SIGNAL(textEdited(QString)), this, SLOT(showSearchResults(QString)));
}


void AppLauncher::deleteObjects()
{
    categoryButtons.clear();
    categoryWidgets.clear();
}


void AppLauncher::initCategory(const QString category, QWidget *widget)
{
    qCDebug(LOG_UI) << "Category" << category;

    QMap<QString, ApplicationItem *> apps = launcher->applicationsByCategory(category);
    foreach (ApplicationItem *app, apps.values()) {
        QWidget *wItem = new IconWidget(app, itemSize(), widget);
        widget->layout()->addWidget(wItem);
        connect(wItem, SIGNAL(widgetPressed()), this, SLOT(runApplication()));
    }
}
