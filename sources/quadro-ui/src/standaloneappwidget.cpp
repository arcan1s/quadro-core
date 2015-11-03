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


#include "standaloneappwidget.h"
#include "ui_standaloneappwidget.h"

#include <QMdiSubWindow>


StandaloneApp::StandaloneApp(QWidget *parent, const QString exec, const int index,
                             const QVariantHash settings)
    : QMainWindow(parent),
      configuration(settings),
      m_exec(exec),
      m_index(index)
{
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;

    ui = new Ui::StandaloneApp;
    ui->setupUi(this);

    createObjects();

    connect(m_application, SIGNAL(ready()), this, SLOT(paintWidget()));
    m_application->startApplication();
}


StandaloneApp::~StandaloneApp()
{
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;

    delete ui;
}


void StandaloneApp::paintWidget()
{
    QList<QWidget *> widgets = m_application->widgets();
    foreach (QWidget *widget, widgets) {
        QMdiSubWindow *subWindow = ui->mdiArea->addSubWindow(widget);
        subWindow->setAttribute(Qt::WA_DeleteOnClose);
        connect(subWindow, SIGNAL(destroyed(QObject *)), this, SLOT(subWindowDestroyed()));
        subWindow->show();
    }

    ui->mdiArea->tileSubWindows();
}


void StandaloneApp::subWindowDestroyed()
{
    if (ui->mdiArea->subWindowList().isEmpty()) {
        qCInfo(LOG_UI) << "No windows remain, close tab";
        emit(destroyWindow(m_index));
    }
}


void StandaloneApp::createObjects()
{
    m_application = new ApplicationLauncherItem(this, m_exec);
}
