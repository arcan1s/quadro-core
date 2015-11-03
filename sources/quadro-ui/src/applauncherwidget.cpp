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

#include <QAction>
#include <QMessageBox>

#include "appiconwidget.h"
#include "dbusoperation.h"
#include "mainwindow.h"
#include "quadrowidget.h"


AppLauncher::AppLauncher(QWidget *parent, LauncherCore *appLauncher,
                         RecentlyCore *recentLauncher, const QVariantHash settings)
    : QMainWindow(parent),
      m_launcher(appLauncher),
      m_recent(recentLauncher),
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

    m_categoryButtons.clear();
    m_categoryWidgets.clear();
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
    return changeCategory(m_categoryButtons.indexOf(action));
}


void AppLauncher::runApplication()
{
    m_recent->addItem(static_cast<AppIconWidget *>(sender())->associatedItem());
}


void AppLauncher::runCustomApplication()
{
    QString exec = ui->lineEdit->text();
    ui->lineEdit->clear();

    ApplicationItem *item = new ApplicationItem(this, exec);
    item->setExec(exec);

    if (item->launch())
        m_recent->addItem(item);
    else
        QMessageBox::critical(this, QApplication::translate("AppLauncher", "Error"),
                              QApplication::translate("AppLauncher", "Could not run application %1").arg(exec));

    sendRequestToUi(QString("Hide"));
}


void AppLauncher::showSearchResults(const QString search)
{
    qCDebug(LOG_UI) << "Search substring" << search;

    // clear
    QLayoutItem *item;
    while ((item = m_categoryWidgets.last()->widget()->layout()->takeAt(0))) {
        delete item->widget();
        delete item;
    }

    // return if none to do here
    if (search.isEmpty()) return ui->stackedWidget->setCurrentIndex(0);
    // add items
    QMap<QString, ApplicationItem *> apps = m_recent->applicationsBySubstr(search);
    QMap<QString, ApplicationItem *> launcherApps = m_launcher->applicationsBySubstr(search);
    foreach (ApplicationItem *app, apps.values() + launcherApps.values()) {
        QWidget *wItem = new AppIconWidget(app, itemSize(), m_categoryWidgets.last()->widget());
        m_categoryWidgets.last()->widget()->layout()->addWidget(wItem);
        connect(wItem, SIGNAL(widgetPressed()), this, SLOT(runApplication()));
    }

    return ui->stackedWidget->setCurrentIndex(ui->stackedWidget->count() - 1);
}


void AppLauncher::createActions()
{
    connect(ui->toolBar, SIGNAL(actionTriggered(QAction *)),
            this, SLOT(changeCategoryByAction(QAction *)));
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(runCustomApplication()));
    connect(ui->lineEdit, SIGNAL(textEdited(QString)), this, SLOT(showSearchResults(QString)));
}


void AppLauncher::createObjects()
{
    QStringList categories = m_launcher->availableCategories();
    foreach (const QString cat, categories) {
        m_categoryButtons.append(ui->toolBar->addAction(cat));
        m_categoryWidgets.append(new QuadroWidget(this, itemSize().width()));
        ui->stackedWidget->addWidget(m_categoryWidgets.last());
        initCategory(cat, m_categoryWidgets.last()->widget());
    }

    // search widget
    m_categoryWidgets.append(new QuadroWidget(this, itemSize().width()));
    ui->stackedWidget->addWidget(m_categoryWidgets.last());
}


void AppLauncher::initCategory(const QString category, QWidget *widget)
{
    qCDebug(LOG_UI) << "Category" << category;

    QMap<QString, ApplicationItem *> apps = m_launcher->applicationsByCategory(category);
    foreach (ApplicationItem *app, apps.values()) {
        QWidget *wItem = new AppIconWidget(app, itemSize(), widget);
        widget->layout()->addWidget(wItem);
        connect(wItem, SIGNAL(widgetPressed()), this, SLOT(runApplication()));
    }
}
