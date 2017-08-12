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
 * @file quadrowidget.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef QUADROWIDGET_H
#define QUADROWIDGET_H

#include <QScrollArea>


class FlowLayout;
class QFocusEvent;

/**
 * @brief The QuadroWidget class provides main UI container
 */
class QuadroWidget : public QScrollArea
{
    Q_OBJECT
    Q_PROPERTY(int grid READ grid)
    Q_PROPERTY(QString title READ title)

public:
    /**
     * @brief QuadroWidget class constructor
     * @param _parent pointer to parent object
     * @param _grid grid size
     * @param _widgetTitle widget title
     * @param _hPolicy horizontal scroll bar policy
     * @param _vPolicy vertical scroll bar policy
     */
    explicit QuadroWidget(QWidget *_parent, const int _grid,
                          const QString _widgetTitle = "none",
                          const Qt::ScrollBarPolicy _hPolicy
                          = Qt::ScrollBarAlwaysOff,
                          const Qt::ScrollBarPolicy _vPolicy
                          = Qt::ScrollBarAsNeeded);
    /**
     * @brief QuadroWidget class destructor
     */
    virtual ~QuadroWidget();
    /**
     * @brief clear widget
     */
    void clearLayout();
    /**
     * @brief grid size
     * @return current widget grid size
     */
    int grid() const;
    /**
     * @brief widget title (will not be shown by default)
     * @return title as a string
     */
    QString title() const;
    // override default method
    /**
     * @brief pointer to UI object
     * @return pointer to QWidget object
     */
    QWidget *widget();

protected:
    /**
     * @brief method which will be called when it receives focus
     * @param _event pointer to focus event
     */
    void focusInEvent(QFocusEvent *_event);
    /**
     * @brief method which will be called to paint UI
     * @remark this method is required to apply custom CSS styles
     * @param _event pointer to paint event
     */
    void paintEvent(QPaintEvent *_event);

public slots:
    /**
     * @brief navigate on widgets inside
     * @param _dx horizontal shift
     * @param _dy vertical shift
     */
    void moveFocus(const int _dx, const int _dy);
    /**
     * @brief move focus down
     */
    void moveFocusDown();
    /**
     * @brief move focus left
     */
    void moveFocusLeft();
    /**
     * @brief move focus right
     */
    void moveFocusRight();
    /**
     * @brief move focus up
     */
    void moveFocusUp();
    /**
     * @brief reset focus
     */
    void resetFocus();

private:
    // ui
    /**
     * @brief main layout object
     */
    FlowLayout *m_layout = nullptr;
    /**
     * @brief main widget object
     */
    QWidget *m_widget = nullptr;
    // methods
    /**
     * @brief create object actions
     */
    void createActions();
    /**
     * @brief create object UI
     */
    void createObjects();
    /**
     * @brief item counts in one string
     * @return item count
     */
    int stringItemCount() const;
    // properties
    /**
     * @brief grid size
     */
    int m_grid = 0;
    /**
     * @brief widget title
     */
    QString m_title;
};


#endif /* QUADROWIDGET_H */
