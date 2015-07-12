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
 * @file dekstopparser.h
 * Header of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#ifndef DESKTOPPARSER_H
#define DESKTOPPARSER_H

#include <QObject>
#include <QSettings>


/**
 * @brief The DesktopParser class provides custom INI parser for desktop files
 * @remark this class creation has been caused by the fact that standard Qt parser
 *         does not recognize semicomma as separator
 */
class DesktopParser : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief DesktopParser class constructor
     * @param parent         pointer to parent item
     * @param debugCmd       show debug messages
     */
    explicit DesktopParser(QObject *parent, const bool debugCmd = false);
    /**
     * @brief DesktopParser class destructor
     */
    ~DesktopParser();
    /**
     * @brief custom QSetting::Format
     * @return format object
     */
    const static QSettings::Format DesktopFormat();
    /**
     * @brief read data from desktop file
     * @param device         read device
     * @param map            settings map
     * @return true if success otherwise returns false
     */
    static bool readDeskopFile(QIODevice &device, QSettings::SettingsMap &map);
    /**
     * @brief write data to desktop file
     * @param device         write device
     * @param map            settings map
     * @return true if success otherwise returns false
     */
    static bool writeDeskopFile(QIODevice &device, const QSettings::SettingsMap &map);

private:
    /**
     * @brief show debug messages. Default is false
     */
    bool debug = false;
};


#endif /* DESKTOPPARSER_H */
