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
 * @file editappwindow.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef EDITAPPWINDOW_H
#define EDITAPPWINDOW_H

#include <QDialog>


class ApplicationItem;

namespace Ui {
class EditAppWindow;
}

/**
 * @brief The EditAppWindow class provide dialog to edit application entry
 */
class EditAppWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief EditAppWindow class constructor
     * @param parent         pointer to parent object
     * @param item           pointer to ApplicationItem object
     */
    explicit EditAppWindow(QWidget *parent, ApplicationItem *item);
    /**
     * @brief EditAppWindow class destructor
     */
    virtual ~EditAppWindow();

public slots:
    /**
     * @brief save ApplicationItem changes
     */
    void saveDesktop();
    /**
     * @brief method which will be called to show window
     */
    void showWindow();

private slots:
    /**
     * @brief category selector
     */
    void addCategory();
    /**
     * @brief executable path selector
     */
    void selectExec();
    /**
     * @brief work directory path selector
     */
    void selectPath();
    /**
     * @brief repaint icon
     * @param _text          current icon name
     */
    void updateIcon(const QString _text);

private:
    // ui
    /**
     * @brief pointer to ui object
     */
    Ui::EditAppWindow *ui = nullptr;
    // backend
    /**
     * @brief pointer to ApplicationItem object
     */
    ApplicationItem *m_item = nullptr;
};


#endif /* EDITAPPWINDOW_H */
