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

#include <language/language.h>

#include <quadrocore/quadrodebug.h>

#include "mainwindow.h"
#include "version.h"


SettingsWindow::SettingsWindow(QWidget *parent, const QString configFile)
    : QMainWindow(parent),
      file(configFile),
      ui(new Ui::SettingsWindow)
{
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;

    ui->setupUi(this);
    addLanguages();
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
    if (fileName.isEmpty()) fileName = file;

    QVariantHash config;
    QSettings settings(fileName, QSettings::IniFormat);

    config[QString("Language")] = Language::defineLanguage(fileName, QString(""));
    settings.beginGroup(QString("Global"));
    config[QString("GridSize")] = settings.value(QString("GridSize"), 150.0);
    config[QString("Language")] = settings.value(QString("Language"), config[QString("Language")]);
    config[QString("RecentItemsCount")] = settings.value(QString("RecentItemsCount"), 20);
    config[QString("ShowHidden")] = settings.value(QString("ShowHidden"), false);
    config[QString("Tabs")] = settings.value(QString("Tabs"), QStringList() <<
                                             QString("quadrofavorites") <<
                                             QString("applauncher") <<
                                             QString("quadrofilemanager"));
    settings.endGroup();

    for (int i=0; i<config.keys().count(); i++)
        qCInfo(LOG_UI) << config.keys()[i] << config[config.keys()[i]];

    return config;
}


void SettingsWindow::closeWindow()
{
    saveSettings();
    close();
    dynamic_cast<MainWindow *>(parent())->updateConfiguration();
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


void SettingsWindow::addLanguages()
{
    ui->comboBox_language->clear();
    ui->comboBox_language->addItems(Language::getAvailableLanguages());
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
    QSettings settings(file, QSettings::IniFormat);

    settings.beginGroup(QString("Global"));
    settings.setValue(QString("GridSize"), config[QString("GridSize")]);
    settings.setValue(QString("Language"), config[QString("Language")]);
    settings.setValue(QString("RecentItemsCount"), config[QString("RecentItemsCount")]);
    settings.setValue(QString("ShowHidden"), config[QString("ShowHidden")]);
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
    config[QString("Language")] = ui->comboBox_language->currentText();
    QStringList tabs;
    // TODO tab settings
    config[QString("Tabs")] = tabs;

    foreach (const QString key, config.keys())
        qCInfo(LOG_UI) << key << config[key];

    return config;
}


void SettingsWindow::setSettings(const QVariantHash config)
{
    // main tab
    int index = ui->comboBox_language->findText(config[QString("Language")].toString());
    ui->comboBox_language->setCurrentIndex(index);
    for (int i=0; i<config[QString("Tabs")].toStringList().count(); i++) {
        // TODO tab settings
    }

    foreach (const QString key, config.keys())
        qCInfo(LOG_UI) << key << config[key];
}
