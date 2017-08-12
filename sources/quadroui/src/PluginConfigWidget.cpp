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
 * @file PluginConfigWidget.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadroui/QuadroUi.h"
#include "ui_PluginConfigWidget.h"

#include <QDBusArgument>

#include <quadrocore/Quadro.h>

using namespace Quadro;


/**
 * @class PluginConfigWidget
 */
/**
 * @fn PluginConfigWidget
 */
PluginConfigWidget::PluginConfigWidget(QWidget *_parent, const QString _group,
                                       const QStringList _enabled)
    : QDialog(_parent)
    , m_group(_group)
    , m_enabled(_enabled)
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
void PluginConfigWidget::addPluginConfigurationPage(const QString &_name,
                                                    QWidget *_configPage)
{
    qCDebug(LOG_UILIB) << "Requesting of adding page for" << _name;
    if (!_configPage) {
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
void PluginConfigWidget::changePage(QTreeWidgetItem *_current,
                                    QTreeWidgetItem *)
{
    qCDebug(LOG_UILIB) << "Current page" << _current->text(0);

    int index = ui->treeWidget->indexOfTopLevelItem(_current);
    ui->stackedWidget->setCurrentIndex(index);
}


/**
 * @fn changePluginRepresentation
 */
void PluginConfigWidget::changePluginRepresentation(QListWidgetItem *_current,
                                                    QListWidgetItem *_previous)
{
    // fallback operations
    if (!_current) {
        qCDebug(LOG_UILIB) << "No current item found";
        return;
    }

    // main cycle
    qCDebug(LOG_UILIB) << "Change data to" << _current->text();

    if ((!_previous) || (m_representations[_previous->text()]->isHidden())) {
        qCInfo(LOG_UILIB) << "Previous item is hidden, try to find active one";
        for (auto wid : m_representations.values()) {
            if (wid->isHidden())
                continue;
            wid->hide();
            // since there is only one (or at least should be) active widget
            // we may break iteration here
            break;
        }
    } else {
        m_representations[_previous->text()]->hide();
    }

    m_representations[_current->text()]->show();
}


/**
 * @fn pluginDisable
 */
void PluginConfigWidget::pluginDisable()
{
    QListWidgetItem *item = ui->listWidget_enabledPlugins->currentItem();
    if (!item) {
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
    if (!item) {
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
    if (!ui->listWidget_enabledPlugins->currentItem()) {
        qCInfo(LOG_UILIB) << "No plugin selected";
        return;
    }

    int currentIndex = ui->listWidget_enabledPlugins->currentRow();
    if (currentIndex == ui->listWidget_enabledPlugins->count() - 1) {
        qCInfo(LOG_UILIB) << "No need to move item from" << currentIndex
                          << "down";
        return;
    }
    QListWidgetItem *item
        = ui->listWidget_enabledPlugins->takeItem(currentIndex);
    qCInfo(LOG_UILIB) << "Move plugin down" << item->text();
    ui->listWidget_enabledPlugins->insertItem(currentIndex + 1, item);
    ui->listWidget_enabledPlugins->setCurrentItem(item);
}


/**
 * @fn pluginMoveUp
 */
void PluginConfigWidget::pluginMoveUp()
{
    if (!ui->listWidget_enabledPlugins->currentItem()) {
        qCInfo(LOG_UILIB) << "No plugin selected";
        return;
    }

    int currentIndex = ui->listWidget_enabledPlugins->currentRow();
    if (currentIndex == 0) {
        qCInfo(LOG_UILIB) << "No need to move item from" << currentIndex
                          << "up";
        return;
    }
    QListWidgetItem *item
        = ui->listWidget_enabledPlugins->takeItem(currentIndex);
    qCInfo(LOG_UILIB) << "Move plugin up" << item->text();
    ui->listWidget_enabledPlugins->insertItem(currentIndex - 1, item);
    ui->listWidget_enabledPlugins->setCurrentItem(item);
}


/**
 * @fn saveSettings
 */
void PluginConfigWidget::saveSettings() const
{
    QStringList plugins;
    auto items = ui->listWidget_enabledPlugins->findItems(
        "*", Qt::MatchWrap | Qt::MatchWildcard);
    for (auto item : items)
        plugins.append(item->text());
    qCInfo(LOG_UILIB) << "Selected plugins" << plugins;

    emit(saveSettingsRequested(plugins));
}


/**
 * @fn createActions
 */
void PluginConfigWidget::createActions()
{
    connect(ui->pushButton_down, SIGNAL(clicked(const bool)), this,
            SLOT(pluginMoveDown()));
    connect(ui->pushButton_left, SIGNAL(clicked(const bool)), this,
            SLOT(pluginEnable()));
    connect(ui->pushButton_right, SIGNAL(clicked(const bool)), this,
            SLOT(pluginDisable()));
    connect(ui->pushButton_up, SIGNAL(clicked(const bool)), this,
            SLOT(pluginMoveUp()));
    connect(ui->treeWidget,
            SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)),
            this, SLOT(changePage(QTreeWidgetItem *, QTreeWidgetItem *)));
    connect(
        ui->listWidget_allPlugins,
        SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this,
        SLOT(changePluginRepresentation(QListWidgetItem *, QListWidgetItem *)));
    connect(
        ui->listWidget_enabledPlugins,
        SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this,
        SLOT(changePluginRepresentation(QListWidgetItem *, QListWidgetItem *)));

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(this, SIGNAL(accepted()), this, SLOT(saveSettings()));
}


/**
 * @fn createObjects
 */
void PluginConfigWidget::createObjects()
{
    // create plugin list
    QStringList knownPluginNames;
    QVariantList plugins = DBusOperations::toNativeType<QVariantList>(
        DBusOperations::sendRequestToLibrary("Plugins",
                                             QVariantList() << m_group)
            .first());
    for (auto &plugin : plugins) {
        QVariantHash metadata
            = qdbus_cast<QVariantHash>(plugin.value<QDBusArgument>());
        QString name = metadata["name"].toString();
        PluginRepresentation *repr = new PluginRepresentation(
            metadata["author"].toString(), metadata["comment"].toString(),
            metadata["group"].toString(), metadata["location"].toString(), name,
            metadata["url"].toString(), metadata["version"].toString(), this);
        PluginRepresentationWidget *wid
            = new PluginRepresentationWidget(this, repr);
        m_representations[name] = wid;
        ui->layout_information->addWidget(wid);
        wid->hide();
        repr->deleteLater();

        knownPluginNames.append(name);
    }

    // found enabled plugins
    knownPluginNames.sort();
    for (auto &plugin : knownPluginNames)
        ui->listWidget_allPlugins->addItem(plugin);
    for (auto &plugin : m_enabled)
        ui->listWidget_enabledPlugins->addItem(plugin);
}
