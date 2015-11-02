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


#ifndef STANDALONEAPPWIDGET_H
#define STANDALONEAPPWIDGET_H

#include <QMainWindow>
#include <QToolButton>

#include <quadro/quadro.h>


namespace Ui {
class StandaloneApp;
}

class StandaloneApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit StandaloneApp(QWidget *parent, const QString exec, const int index = 0,
                           const QVariantHash settings = QVariantHash());
    virtual ~StandaloneApp();

public slots:
    void paintWidget();

signals:
    void destroyWindow(const int index);

private slots:
    void subWindowDestroyed();

private:
    // ui
    Ui::StandaloneApp *ui = nullptr;
    // backend
    void createObjects();
    ApplicationLauncherItem *application = nullptr;
    // configuration
    QVariantHash configuration;
    QString m_exec;
    int m_index;
};


#endif /* STANDALONEAPPWIDGET_H */
