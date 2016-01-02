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
 * @file pluginconfigwidget.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef PLUGINCONFIGWIDGET_H
#define PLUGINCONFIGWIDGET_H

#include <QMainWindow>
#include <QTreeWidgetItem>


namespace Ui {
class PluginConfigWidget;
}

/**
 * @brief The PluginConfigWidget class provides UI for plugin configuration
 */
class PluginConfigWidget : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief PluginConfigWidget class constructor
     * @param parent         pointer to parent object
     * @param group          plugin group
     * @param enabled        names of enabled plugins
     */
    explicit PluginConfigWidget(QWidget *parent, const QString group,
                                const QStringList enabled);
    /**
     * @brief PluginConfigWidget class destructor
     */
    virtual ~PluginConfigWidget();
    /**
     * @brief creates plugin configuration page
     * @param _name          plugin name
     * @param _configPage    pointer to configuration interface. It may be nullptr
     *                       that means that no page will be created
     */
    void addPluginConfigurationPage(const QString _name, QWidget *_configPage);

private slots:
    /**
     * @brief slot which will be called when item in the tree widget will be
     * activated
     * @param _current       pointer to current item
     */
    void changePage(QTreeWidgetItem *_current, QTreeWidgetItem *);
    /**
     * @brief slot which will be called to disable plugin
     */
    void pluginDisable();
    /**
     * @brief slot which will be called to enable plugin
     */
    void pluginEnable();
    /**
     * @brief slot which will be called to move plugin down
     */
    void pluginMoveDown();
    /**
     * @brief slot which will be called to move plugin up
     */
    void pluginMoveUp();

private:
    // ui
    /**
     * @brief pointer to UI object
     */
    Ui::PluginConfigWidget *ui = nullptr;
    // backend
    /**
     * @brief additional method to create window actions
     */
    void createActions();
    /**
     * @brief additional method to create objects
     */
    void createObjects();
    /**
     * @brief associated plugin group
     */
    QString m_group;
    /**
     * @brief list of enabled plugin names
     */
    QStringList m_enabled;
};


#endif /* PLUGINCONFIGWIDGET_H */
