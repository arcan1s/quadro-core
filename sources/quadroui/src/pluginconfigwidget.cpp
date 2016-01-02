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
 * @file pluginconfigwidget.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadroui/quadroui.h"
#include "ui_pluginconfigwidget.h"

#include <QDBusArgument>
#include <QListWidgetItem>

#include <quadrocore/quadro.h>


/**
 * @class PluginConfigWidget
 */
/**
 * @fn PluginConfigWidget
 */
PluginConfigWidget::PluginConfigWidget(QWidget *parent, const QString group,
                                       const QStringList enabled)
    : QMainWindow(parent)
    , m_group(group)
    , m_enabled(enabled)
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;

    ui = new Ui::PluginConfigWidget;
    ui->setupUi(this);

    createObjects();
    createActions();
}


/**
 * @fn ~PluginConfigWidget
 */
PluginConfigWidget::~PluginConfigWidget()
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;

    delete ui;
}


/**
 * @fn addPluginConfigurationPage
 */
void PluginConfigWidget::addPluginConfigurationPage(const QString _name,
                                                    QWidget *_configPage)
{
    qCDebug(LOG_UILIB) << "Requesting of adding page for" << _name;
    if (_configPage == nullptr) {
        qCInfo(LOG_UILIB) << "No configuration interface found for" << _name;
        return;
    }

    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0, _name);
    ui->stackedWidget->addWidget(_configPage);
}


/**
 * @fn changePage
 */
void PluginConfigWidget::changePage(QTreeWidgetItem *_current, QTreeWidgetItem *)
{
    qCDebug(LOG_UILIB) << "Current page" << _current->text(0);

    for (int i=0; i<ui->treeWidget->topLevelItemCount(); i++) {
        if (_current != ui->treeWidget->topLevelItem(i))
            continue;
        qCInfo(LOG_UILIB) << "Change tab to" << i;
        ui->stackedWidget->setCurrentIndex(i);
        break;
    }
}


/**
 * @fn pluginDisable
 */
void PluginConfigWidget::pluginDisable()
{
    QListWidgetItem *item = ui->listWidget_enabledPlugins->currentItem();
    if (item == nullptr) {
        qCInfo(LOG_UILIB) << "No plugin selected";
        return;
    }

    qCInfo(LOG_UILIB) << "Disable plugin" << item->text();
    ui->listWidget_enabledPlugins->removeItemWidget(item);
    delete item;
}


/**
 * @fn pluginEnable
 */
void PluginConfigWidget::pluginEnable()
{
    QListWidgetItem *item = ui->listWidget_allPlugins->currentItem();
    if (item == nullptr) {
        qCInfo(LOG_UILIB) << "No plugin selected";
        return;
    }

    qCInfo(LOG_UILIB) << "Enable plugin" << item->text();
    // do not use copy here because if plugin is already added it will result to
    // undefined behavior, see http://doc.qt.io/qt-5/qlistwidget.html#addItem-1
    // for more details
    ui->listWidget_enabledPlugins->addItem(item->text());
}


/**
 * @fn pluginMoveDown
 */
void PluginConfigWidget::pluginMoveDown()
{
    if (ui->listWidget_enabledPlugins->currentItem() == nullptr) {
        qCInfo(LOG_UILIB) << "No plugin selected";
        return;
    }

    int currentIndex = ui->listWidget_enabledPlugins->currentRow();
    if (currentIndex == ui->listWidget_enabledPlugins->count() - 1) {
        qCInfo(LOG_UILIB) << "No need to move item from" << currentIndex << "down";
        return;
    }
    QListWidgetItem *item = ui->listWidget_enabledPlugins->takeItem(currentIndex);
    qCInfo(LOG_UILIB) << "Move plugin down" << item->text();
    ui->listWidget_enabledPlugins->insertItem(currentIndex + 1, item);
    ui->listWidget_enabledPlugins->setCurrentItem(item);
}


/**
 * @fn pluginMoveUp
 */
void PluginConfigWidget::pluginMoveUp()
{
    if (ui->listWidget_enabledPlugins->currentItem() == nullptr) {
        qCInfo(LOG_UILIB) << "No plugin selected";
        return;
    }

    int currentIndex = ui->listWidget_enabledPlugins->currentRow();
    if (currentIndex == 0) {
        qCInfo(LOG_UILIB) << "No need to move item from" << currentIndex << "up";
        return;
    }
    QListWidgetItem *item = ui->listWidget_enabledPlugins->takeItem(currentIndex);
    qCInfo(LOG_UILIB) << "Move plugin up" << item->text();
    ui->listWidget_enabledPlugins->insertItem(currentIndex - 1, item);
    ui->listWidget_enabledPlugins->setCurrentItem(item);
}


/**
 * @fn createActions
 */
void PluginConfigWidget::createActions()
{
    connect(ui->pushButton_down, SIGNAL(clicked(const bool)), this, SLOT(pluginMoveDown()));
    connect(ui->pushButton_left, SIGNAL(clicked(const bool)), this, SLOT(pluginEnable()));
    connect(ui->pushButton_right, SIGNAL(clicked(const bool)), this, SLOT(pluginDisable()));
    connect(ui->pushButton_up, SIGNAL(clicked(const bool)), this, SLOT(pluginMoveUp()));
    connect(ui->treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)),
            this, SLOT(changePage(QTreeWidgetItem *, QTreeWidgetItem *)));
}


/**
 * @fn createObjects
 */
void PluginConfigWidget::createObjects()
{
    // create plugin list
    QStringList knownPluginNames;
    QVariantList plugins = DBusOperations::toNative<QVariantList>(
        DBusOperations::sendRequestToLibrary(QString("Plugins"),
                                             QVariantList() << m_group).first());
    for (auto plugin : plugins) {
        QVariantHash metadata = qdbus_cast<QVariantHash>(plugin.value<QDBusArgument>());
        PluginRepresentation *repr = new PluginRepresentation(
            metadata[QString("author")].toString(), metadata[QString("comment")].toString(),
            metadata[QString("group")].toString(), metadata[QString("location")].toString(),
            metadata[QString("name")].toString(), metadata[QString("url")].toString(),
            metadata[QString("version")].toString(), this);
        ui->scrollAreaWidgetContents_plugins->layout()->addWidget(
            new PluginRepresentationWidget(this, repr));
        repr->deleteLater();

        knownPluginNames.append(metadata[QString("name")].toString());
    }

    // found enabled plugins
    knownPluginNames.sort();
    for (auto plugin : knownPluginNames)
        ui->listWidget_allPlugins->addItem(plugin);
    for (auto plugin : m_enabled)
        ui->listWidget_enabledPlugins->addItem(plugin);
}
