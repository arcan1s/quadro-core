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

#include <flowlayout/flowlayout.h>
#include <pdebug/pdebug.h>


AppLauncher::AppLauncher(QWidget *parent, const QVariantMap settings,
                         const bool debugCmd)
    : QWidget(parent),
      debug(debugCmd),
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
    if (launcher != nullptr) delete launcher;
    delete ui;
}


void AppLauncher::changeCategory(const int index)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << "Index" << index;
    if ((index == -1) || (index >= ui->stackedWidget->count())) return;

    return ui->stackedWidget->setCurrentIndex(index);
}


void AppLauncher::changeCategoryByButton()
{
    if (debug) qDebug() << PDEBUG;

    int index = -1;
    for (int i=0; i<categoryButtons.count(); i++) {
        if (categoryButtons[i] != dynamic_cast<QPushButton *>(sender())) continue;
        index = i;
        break;
    }

    return changeCategory(index);
}


void AppLauncher::createActions()
{
    if (debug) qDebug() << PDEBUG;
}


void AppLauncher::createObjects()
{
    if (debug) qDebug() << PDEBUG;

    launcher = new LauncherCore(this, debug);
    launcher->initApplications();

    QStringList categories = launcher->availableCategories();
    for (int i=0; i<categories.count(); i++) {
        categoryButtons.append(new QPushButton(categories[i], this));
        ui->layout_buttons->addWidget(categoryButtons[i]);

        categoryWidgets.append(new QWidget(this));
        categoryWidgets[i]->setLayout(new FlowLayout(categoryWidgets[i]));
        initCategory(categories[i], i);
        ui->stackedWidget->addWidget(categoryWidgets[i]);

        connect(categoryButtons[i], SIGNAL(pressed()), this, SLOT(changeCategoryByButton()));
    }
}


void AppLauncher::deleteObjects()
{
    if (debug) qDebug() << PDEBUG;

    categoryButtons.clear();
    categoryWidgets.clear();
}


void AppLauncher::initCategory(const QString category, const int index)
{
    if (debug) qDebug() << PDEBUG;
    if (debug) qDebug() << PDEBUG << "Category" << category;
    if (debug) qDebug() << PDEBUG << "Index" << index;

    QMap<QString, ApplicationItem *> apps = launcher->applicationsByCategory(category);
    for (int i=0; i<apps.keys().count(); i++) {
        QPushButton *item = new QPushButton(categoryWidgets[index]);
        item->setText(apps.keys()[i]);
        item->setIcon(apps[apps.keys()[i]]->icon());

        categoryWidgets[index]->layout()->addWidget(item);
        connect(item, SIGNAL(pressed()), apps[apps.keys()[i]], SLOT(launch()));
    }
}
