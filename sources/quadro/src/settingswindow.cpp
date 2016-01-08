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

#include "settingswindow.h"
#include "ui_settingswindow.h"

#include <QFileDialog>
#include <QPushButton>
#include <QSettings>

#include <quadrocore/quadrodebug.h>

#include "quadromainwindow.h"
#include "version.h"


SettingsWindow::SettingsWindow(QWidget *parent, const QString configFile)
    : QMainWindow(parent),
      m_file(configFile),
      ui(new Ui::SettingsWindow)
{
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;

    ui->setupUi(this);
    createActions();
}


SettingsWindow::~SettingsWindow()
{
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;

    delete ui;
}


QVariantHash SettingsWindow::getDefault()
{
    return getSettings(QString("/dev/null"));
}


QVariantHash SettingsWindow::getSettings(QString fileName)
{
    if (fileName.isEmpty())
        fileName = m_file;

    QVariantHash config;
    QSettings settings(fileName, QSettings::IniFormat);

    settings.beginGroup(QString("UI"));
    config[QString("Tabs")] = settings.value(QString("Tabs"), QStringList() <<
                                             QString("favlauncher") <<
                                             QString("applauncher") <<
                                             QString("filemanager") <<
                                             QString("webpage"));
    settings.endGroup();

    for (int i=0; i<config.keys().count(); i++)
        qCInfo(LOG_UI) << config.keys()[i] << config[config.keys()[i]];

    return config;
}


void SettingsWindow::closeWindow()
{
    saveSettings();
    close();
    dynamic_cast<QuadroMainWindow *>(parent())->updateConfiguration();
}


void SettingsWindow::restoreSettings()
{
    setSettings(getSettings());
}


void SettingsWindow::setDefault()
{
    setSettings(getDefault());
    if (sender() != ui->buttonBox->button(QDialogButtonBox::Reset))
        saveSettings();
}


void SettingsWindow::showWindow()
{
    setSettings(getSettings());

    show();
}


void SettingsWindow::keyPressEvent(QKeyEvent *pressedKey)
{
    if (pressedKey->key() == Qt::Key_Escape)
        close();
}


void SettingsWindow::changePage(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(previous);

    for (int i=0; i<ui->treeWidget->topLevelItemCount(); i++) {
        if (current != ui->treeWidget->topLevelItem(i)) continue;
        ui->stackedWidget->setCurrentIndex(i);
        break;
    }
}


void SettingsWindow::saveSettings()
{
    QVariantHash config = readSettings();
    QSettings settings(m_file, QSettings::IniFormat);

    settings.beginGroup(QString("UI"));
    settings.setValue(QString("Tabs"), config[QString("Tabs")]);
    settings.endGroup();

    settings.sync();
}


void SettingsWindow::createActions()
{
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked(bool)), this, SLOT(closeWindow()));
    connect(ui->buttonBox->button(QDialogButtonBox::Reset), SIGNAL(clicked(bool)), this, SLOT(restoreSettings()));
    connect(ui->buttonBox->button(QDialogButtonBox::RestoreDefaults), SIGNAL(clicked(bool)), this, SLOT(setDefault()));
    connect(ui->treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)),
            this, SLOT(changePage(QTreeWidgetItem *, QTreeWidgetItem *)));
}


QVariantHash SettingsWindow::readSettings()
{
    QVariantHash config;

    // main tab
    QStringList tabs;
    // TODO tab settings
    config[QString("Tabs")] = tabs;

    for (auto key : config.keys())
        qCInfo(LOG_UI) << key << config[key];

    return config;
}


void SettingsWindow::setSettings(const QVariantHash config)
{
    // main tab
    for (int i=0; i<config[QString("Tabs")].toStringList().count(); i++) {
        // TODO tab settings
    }

    for (auto key : config.keys())
        qCInfo(LOG_UI) << key << config[key];
}
