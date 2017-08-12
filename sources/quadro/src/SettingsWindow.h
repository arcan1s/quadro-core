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

#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QKeyEvent>
#include <QMainWindow>
#include <QTreeWidgetItem>


namespace Ui
{
class SettingsWindow;
}

class SettingsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *_parent = nullptr,
                            const QString _configFile = "");
    virtual ~SettingsWindow();
    QVariantHash getDefault();
    QVariantHash getSettings(QString _fileName = "");

public slots:
    void closeWindow();
    void restoreSettings();
    void setDefault();
    void showWindow();

protected:
    // ESC pressed event
    void keyPressEvent(QKeyEvent *_pressedKey);

private slots:
    void changePage(QTreeWidgetItem *_current, QTreeWidgetItem *);
    void saveSettings();

private:
    QString m_file;
    Ui::SettingsWindow *ui;
    void createActions();
    QVariantHash readSettings();
    void setSettings(const QVariantHash &_config);
};


#endif /* SETTINGSWINDOW_H */
