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
 * @file PluginConfigWidget.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef PLUGINCONFIGWIDGET_H
#define PLUGINCONFIGWIDGET_H

#include <QDialog>
#include <QListWidgetItem>
#include <QTreeWidgetItem>


namespace Ui
{
class PluginConfigWidget;
};

/**
 * @namespace Quadro
 */
namespace Quadro
{
class PluginRepresentationWidget;

/**
 * @brief The PluginConfigWidget class provides UI for plugin configuration
 */
class PluginConfigWidget : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief PluginConfigWidget class constructor
     * @param _parent pointer to parent object
     * @param _group plugin group
     * @param _enabled names of enabled plugins
     */
    explicit PluginConfigWidget(QWidget *parent, const QString _group,
                                const QStringList _enabled);

    /**
     * @brief PluginConfigWidget class destructor
     */
    virtual ~PluginConfigWidget();

    /**
     * @brief creates plugin configuration page
     * @param _name plugin name
     * @param _configPage pointer to configuration interface. It may be nullptr
     * that means that no page will be created
     */
    void addPluginConfigurationPage(const QString &_name, QWidget *_configPage);

signals:

    /**
     * @brief signal which will be emitted each time when settings save is
     * requested
     * @param _plugins list of plugins which is set to enabled
     */
    void saveSettingsRequested(const QStringList &_plugins) const;

private slots:

    /**
     * @brief slot which will be called when item in the tree widget will be
     * activated
     * @param _current pointer to current item
     */
    void changePage(QTreeWidgetItem *_current, QTreeWidgetItem *);

    /**
     * @brief change enabled plugin information page
     * @param _current pointer to current active item
     * @param _previous pointer to previous active item
     */
    void changePluginRepresentation(QListWidgetItem *_current,
                                    QListWidgetItem *_previous);

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

    /**
     * @brief method which will be called to save settings
     */
    void saveSettings() const;

private:
    // ui
    /**
     * @brief pointer to UI object
     */
    Ui::PluginConfigWidget *ui = nullptr;
    QHash<QString, PluginRepresentationWidget *> m_representations;
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
};


#endif /* PLUGINCONFIGWIDGET_H */
