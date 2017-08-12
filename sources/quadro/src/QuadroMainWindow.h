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


#ifndef QUADROMAINWINDOW_H
#define QUADROMAINWINDOW_H

#include <QAction>
#include <QApplication>
#include <QMainWindow>


namespace Quadro
{
class QuadroCore;
};
class SettingsWindow;

namespace Ui
{
class QuadroMainWindow;
};

class QuadroMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuadroMainWindow(QWidget *_parent, const QVariantHash _args);
    virtual ~QuadroMainWindow();

public slots:
    void changeTab(const int _index = -1);
    void closeMainWindow();
    void showSettingsWindow();
    void updateConfiguration(const QVariantHash &_args);
    // container settings
    void createContainer(const QStringList &_exec, const QString &_name);
    void createWebContainer(const QString &_url, const bool _showOpen);
    void removeContainer(const int _index);

signals:
    void needToBeConfigured();

private slots:
    void changeTabByAction(QAction *_action);
    void clearTabs();
    void initTabs();

protected:
    void closeEvent(QCloseEvent *_event);

private:
    // ui
    QList<QAction *> tabActions;
    SettingsWindow *settingsWindow = nullptr;
    Ui::QuadroMainWindow *ui = nullptr;
    // backend
    void createActions();
    void createDBusSession();
    void createObjects();
    void deleteObjects();
    QString m_configPath;
    // library
    Quadro::QuadroCore *m_core = nullptr;
    // configuration
    QVariantHash m_configuration;
    QList<QVariantHash> m_plugins;
};


#endif /* QUADROMAINWINDOW_H */
