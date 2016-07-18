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
 * @file pluginrepresentationwidget.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadroui/quadroui.h"
#include "ui_pluginrepresentationwidget.h"

#include <quadrocore/quadro.h>


/**
 * @class PluginRepresentationWidget
 */
/**
 * @fn PluginRepresentationWidget
 */
PluginRepresentationWidget::PluginRepresentationWidget(
    QWidget *parent, PluginRepresentation *representation)
    : QWidget(parent)
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;

    ui = new Ui::PluginRepresentationWidget;
    ui->setupUi(this);

    ui->groupBox->setTitle(representation->name());
    ui->label_versionValue->setText(representation->version());
    ui->label_commentValue->setText(representation->comment());
    ui->label_authorValue->setText(representation->author());
    ui->label_urlValue->setText(
        QString("<a href=\"%1\">%1</a>").arg(representation->url()));
    ui->label_locationValue->setText(representation->location());
    ui->label_groupValue->setText(representation->group());
}


/**
 * @fn ~PluginRepresentationWidget
 */
PluginRepresentationWidget::~PluginRepresentationWidget()
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;

    delete ui;
}
