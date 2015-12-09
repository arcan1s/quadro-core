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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QApplication>
#include <QMainWindow>

#include <quadrocore/quadro.h>


class SettingsWindow;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent,
                        const QVariantHash args = QVariantHash());
    virtual ~MainWindow();

public slots:
    void changeTab(const int index = -1);
    void closeMainWindow();
    void showSettingsWindow();
    void updateConfiguration(const QVariantHash args = QVariantHash());
    // container settings
    void createContainer(const QStringList exec, const QString name);
    void removeContainer(const int index);

signals:
    void needToBeConfigured();

private slots:
    void changeTabByAction(QAction *action);
    void clearTabs();
    void initTabs();

protected:
    void closeEvent(QCloseEvent *event);

private:
    // ui
    QList<QAction *> tabActions;
    SettingsWindow *settingsWindow = nullptr;
    Ui::MainWindow *ui = nullptr;
    // backend
    void createActions();
    void createDBusSession();
    void createObjects();
    void deleteObjects();
    QString m_configPath;
    // library
    QuadroCore *m_core = nullptr;
    // configuration
    QVariantHash m_configuration;
    QList<QVariantHash> m_plugins;
};


#endif /* MAINWINDOW_H */
