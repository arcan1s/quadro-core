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
 * @file iconwidget.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef ICONWIDGET_H
#define ICONWIDGET_H

#include <QSize>
#include <QWidget>


class QIcon;
class QKeyEvent;
class QLabel;
class QMouseEvent;

/**
 * @brief The IconWidget class provides generic UI representation
 */
class IconWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief IconWidget class constructor
     * @param size           item size
     * @param parent         pointer to parent object
     */
    explicit IconWidget(const QSize size, QWidget *parent);
    /**
     * @brief IconWidget class destructor
     */
    virtual ~IconWidget();
    /**
     * @brief method to generate icon size
     * @param _size          source size
     * @return converted QSize object
     */
    inline QSize convertSize(const QSize _size) const;
    /**
     * @brief set icon to UI
     * @param _icon          new icon object
     */
    void setIcon(const QIcon _icon);
    /**
     * @brief set text to UI
     * @param _text          new text
     */
    void setText(const QString _text);

public slots:
    /**
     * @brief method which will be called on context menu request
     * @param _pos           current mouse position
     */
    virtual void showContextMenu(const QPoint &_pos) = 0;

signals:
    /**
     * @brief signal which will be emitted when widget will be pressed
     */
    void widgetPressed();

protected:
    /**
     * @brief method which will be called on key press event
     * @param _pressedKey    pointer to pressed key
     */
    void keyPressEvent(QKeyEvent *_pressedKey);
    /**
     * @brief method which will be called on mouse event
     * @param _event         pointer to mouse event
     */
    void mousePressEvent(QMouseEvent *_event);
    /**
     * @brief method which will be called to paint UI
     * @remark this method is required to apply custom CSS styles
     * @param _event         pointer to paint event
     */
    void paintEvent(QPaintEvent *_event);

private:
    // ui
    /**
     * @brief pointer to QLabel with icon
     */
    QLabel *m_iconLabel = nullptr;
    /**
     * @brief pointer to QLabel with text
     */
    QLabel *m_textLabel = nullptr;
    // properties
    /**
     * @brief UI size
     */
    QSize m_size;
};


#endif /* ICONWIDGET_H */
