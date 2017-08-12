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
 * @file pluginrepresentationwidget.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef PLUGINREPRESENTATIONWIDGET_H
#define PLUGINREPRESENTATIONWIDGET_H

#include <QWidget>


class PluginRepresentation;

namespace Ui
{
class PluginRepresentationWidget;
}

/**
 * @brief The PluginRepresentationWidget class provides UI for
 * PluginRepresentation class
 */
class PluginRepresentationWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief PluginRepresentationWidget class constructor
     * @param _parent pointer to parent object
     * @param _representation pointer to representation object
     *
     */
    explicit PluginRepresentationWidget(QWidget *_parent,
                                        PluginRepresentation *_representation);
    /**
     * @brief PluginRepresentationWidget class destructor
     */
    virtual ~PluginRepresentationWidget();

private:
    // ui
    /**
     * @brief pointer to UI object
     */
    Ui::PluginRepresentationWidget *ui = nullptr;
};


#endif /* PLUGINREPRESENTATIONWIDGET_H */
