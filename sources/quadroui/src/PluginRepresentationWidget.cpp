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
 * @file PluginRepresentationWidget.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadroui/QuadroUi.h"
#include "ui_PluginRepresentationWidget.h"

#include <quadrocore/Quadro.h>

using namespace Quadro;


/**
 * @class PluginRepresentationWidget
 */
/**
 * @fn PluginRepresentationWidget
 */
PluginRepresentationWidget::PluginRepresentationWidget(
    QWidget *_parent, PluginRepresentation *_representation)
    : QWidget(_parent)
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;

    ui = new Ui::PluginRepresentationWidget;
    ui->setupUi(this);

    ui->groupBox->setTitle(_representation->name());
    ui->label_versionValue->setText(_representation->version());
    ui->label_commentValue->setText(_representation->comment());
    ui->label_authorValue->setText(_representation->author());
    ui->label_urlValue->setText(
        QString("<a href=\"%1\">%1</a>").arg(_representation->url()));
    ui->label_locationValue->setText(_representation->location());
    ui->label_groupValue->setText(_representation->group());
}


/**
 * @fn ~PluginRepresentationWidget
 */
PluginRepresentationWidget::~PluginRepresentationWidget()
{
    qCDebug(LOG_UILIB) << __PRETTY_FUNCTION__;

    delete ui;
}
