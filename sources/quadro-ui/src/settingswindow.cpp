/***************************************************************************
 *   This file is part of netctl-gui                                       *
 *                                                                         *
 *   netctl-gui is free software: you can redistribute it and/or           *
 *   modify it under the terms of the GNU General Public License as        *
 *   published by the Free Software Foundation, either version 3 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   netctl-gui is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with netctl-gui. If not, see http://www.gnu.org/licenses/       *
 ***************************************************************************/

#include "settingswindow.h"
#include "ui_settingswindow.h"

#include <QFileDialog>
#include <QPushButton>
#include <QSettings>

#include <language/language.h>

#include "mainwindow.h"
#include "quadro/quadrodebug.h"
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


QVariantMap SettingsWindow::getDefault()
{
    return getSettings(QString("/dev/null"));
}


QVariantMap SettingsWindow::getSettings(QString fileName)
{
    if (fileName.isEmpty()) fileName = file;

    QVariantMap config;
    QSettings settings(fileName, QSettings::IniFormat);

    config[QString("Language")] = Language::defineLanguage(fileName, QString(""));
    settings.beginGroup(QString("Global"));
    config[QString("GridSize")] = settings.value(QString("GridSize"), 150.0);
    config[QString("Language")] = settings.value(QString("Language"), config[QString("Language")]);
    config[QString("Tabs")] = settings.value(QString("Tabs"), QStringList() <<
                                             QString("favorites") <<
                                             QString("applauncher"));
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
    QVariantMap config = readSettings();
    QSettings settings(file, QSettings::IniFormat);

    settings.beginGroup(QString("Global"));
    settings.setValue(QString("GridSize"), config[QString("GridSize")]);
    settings.setValue(QString("Language"), config[QString("Language")]);
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


// ESC press event
void SettingsWindow::keyPressEvent(QKeyEvent *pressedKey)
{
    if (pressedKey->key() == Qt::Key_Escape)
        close();
}


QVariantMap SettingsWindow::readSettings()
{
    QVariantMap config;

    // main tab
    config[QString("Language")] = ui->comboBox_language->currentText();
    QStringList tabs;
    // TODO tab settings
    config[QString("Tabs")] = tabs;

    for (int i=0; i<config.keys().count(); i++)
        qCInfo(LOG_UI) << config.keys()[i] << config[config.keys()[i]];

    return config;
}


void SettingsWindow::setSettings(const QVariantMap config)
{
    // main tab
    int index = ui->comboBox_language->findText(config[QString("Language")].toString());
    ui->comboBox_language->setCurrentIndex(index);
    for (int i=0; i<config[QString("Tabs")].toStringList().count(); i++) {
        // TODO tab settings
    }

    for (int i=0; i<config.keys().count(); i++)
        qCInfo(LOG_UI) << config.keys()[i] << config[config.keys()[i]];
}
