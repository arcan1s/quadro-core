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
 * @file standaloneappwidget.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef STANDALONEAPPWIDGET_H
#define STANDALONEAPPWIDGET_H

#include <QMainWindow>
#include <QToolButton>


class StandaloneApplicationItem;

namespace Ui {
class StandaloneAppWidget;
}

/**
 * @brief The StandaloneAppWidget class provides standalone application UI representation
 */
class StandaloneAppWidget : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief StandaloneAppWidget class constructor
     * @param parent         pointer to parent object
     * @param exec           application executable
     * @param index          tab index
     * @param settings       application settings
     */
    explicit StandaloneAppWidget(QWidget *parent, const QStringList exec,
                                 const int index, const QVariantHash settings = QVariantHash());
    /**
     * @brief StandaloneAppWidget class destructor
     */
    virtual ~StandaloneAppWidget();

public slots:
    /**
     * @brief method which will be called to paint application
     */
    void paintWidget();

signals:
    /**
     * @brief signal which will be emitted when all windows will be closed
     * @param _index         tab index
     */
    void destroyWindow(const int _index);

private slots:
    /**
     * @brief method which will be called when any window will be closed
     */
    void subWindowDestroyed();

private:
    // ui
    /**
     * @brief pointer to UI object
     */
    Ui::StandaloneAppWidget *ui = nullptr;
    // backend
    /**
     * @brief additional method to create objects
     */
    void createObjects();
    /**
     * @brief generated StandaloneApplicationItem object
     */
    StandaloneApplicationItem *m_application = nullptr;
    // configuration
    /**
     * @brief application configuration
     */
    QVariantHash m_configuration;
    /**
     * @brief application executable
     */
    QStringList m_exec;
    /**
     * @brief tab index
     */
    int m_index;
};


#endif /* STANDALONEAPPWIDGET_H */
