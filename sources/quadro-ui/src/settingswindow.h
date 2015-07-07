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

#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QKeyEvent>
#include <QMainWindow>
#include <QTreeWidgetItem>


class MainWindow;

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr,
                            const bool debugCmd = false,
                            const QString configFile = QString(""));
    ~SettingsWindow();
    QVariantMap getDefault();
    QVariantMap getSettings(QString fileName = QString(""));

public slots:
    void closeWindow();
    void restoreSettings();
    void setDefault();
    void showWindow();

private slots:
    void addLanguages();
    void changePage(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void saveSettings();

private:
    bool debug;
    QString file;
    Ui::SettingsWindow *ui;
    void createActions();
    // ESC pressed event
    void keyPressEvent(QKeyEvent *pressedKey);
    QVariantMap readSettings();
    void setSettings(const QVariantMap config);
};


#endif /* SETTINGSWINDOW_H */