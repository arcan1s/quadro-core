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


#ifndef APPLAUNCHERWIDGET_H
#define APPLAUNCHERWIDGET_H

#include <QMainWindow>

#include <quadro/quadro.h>


class QAction;
class QuadroWidget;

namespace Ui {
class AppLauncher;
}

class AppLauncher : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppLauncher(QWidget *parent, LauncherCore *appLauncher,
                         RecentlyCore *recentLauncher,
                         const QVariantHash settings = QVariantHash());
    virtual ~AppLauncher();
    inline QSize itemSize();

public slots:
    void changeCategory(const int index);

private slots:
    void changeCategoryByAction(QAction *action);
    void runApplication();
    void runCustomApplication();
    void showSearchResults(const QString search);

private:
    // ui
    QList<QAction *> m_categoryButtons;
    QList<QuadroWidget *> m_categoryWidgets;
    Ui::AppLauncher *ui = nullptr;
    // backend
    void createActions();
    void createObjects();
    void initCategory(const QString category, QWidget *widget);
    LauncherCore *m_launcher = nullptr;
    RecentlyCore *m_recent = nullptr;
    // configuration
    QVariantHash configuration;
};


#endif /* APPLAUNCHERWIDGET_H */
