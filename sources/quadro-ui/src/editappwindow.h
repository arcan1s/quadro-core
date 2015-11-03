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


#ifndef EDITAPPWINDOW_H
#define EDITAPPWINDOW_H

#include <QDialog>

#include <quadro/quadro.h>


namespace Ui {
class EditAppWindow;
}

class EditAppWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditAppWindow(QWidget *parent, ApplicationItem *item);
    virtual ~EditAppWindow();

public slots:
    void saveDesktop();
    void showWindow();

private slots:
    void addCategory();
    void selectExec();
    void selectPath();
    void updateIcon(const QString text);

private:
    // ui
    Ui::EditAppWindow *ui = nullptr;
    // backend
    ApplicationItem *m_item = nullptr;
};


#endif /* EDITAPPWINDOW_H */
