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
 * @file desktopparser.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include <QDebug>

#include <quadro/quadro.h>
#include <pdebug/pdebug.h>


/**
 * @class DesktopParser
 */
/**
 * @fn DesktopParser
 */
DesktopParser::DesktopParser(QObject *parent, const bool debugCmd)
    : QObject(parent),
      debug(debugCmd)
{
}


/**
 * @fn ~DesktopParser
 */
DesktopParser::~DesktopParser()
{
    if (debug) qDebug() << PDEBUG;
}


/**
 * @fn DesktopFormat
 */
const QSettings::Format DesktopParser::DesktopFormat()
{
    return QSettings::registerFormat(QString("desktop"), DesktopParser::readDeskopFile,
                                     DesktopParser::writeDeskopFile);
}


/**
 * @fn readDeskopFile
 */
bool DesktopParser::readDeskopFile(QIODevice &device, QSettings::SettingsMap &map)
{
    // open file
    qDebug() << "this";
//     if (!device.open(QIODevice::ReadOnly)) return false;
    // parse
    while (true) {
        QString fileStr = QString(device.readLine()).trimmed();
        qDebug() << fileStr;
        // empty line, wtf?
        if ((fileStr.isEmpty()) && (!device.atEnd())) continue;
        // start line comments
        if ((fileStr[0] == QChar('#')) && (!device.atEnd())) continue;
        if ((fileStr[0] == QChar(';')) && (!device.atEnd())) continue;
        // comments at the end of the line
        if ((fileStr.contains(QString(" ;"))) && (!device.atEnd()))
            fileStr = fileStr.split(QString(" ;"))[0];
        // assing value
        if (fileStr.contains(QChar('='))) {
            QStringList value = fileStr.split(QChar('='));
            QString key = value.takeFirst();
            map[QString("Desktop Entry/%1").arg(key)] = value.join(QChar('='));
        }
        // break at the end
        if (device.atEnd()) break;
    }
    // close file
//     device.close();

    return true;
}


/**
 * @fn writeDeskopFile
 */
bool DesktopParser::writeDeskopFile(QIODevice &device, const QSettings::SettingsMap &map)
{
    // open file
    if (!device.open(QIODevice::WriteOnly)) return false;
    // write
    for (int i=0; i<map.keys().count(); i++) {
        QByteArray string = QString("%1=%2\n").arg(map.keys()[i]).arg(map[map.keys()[i]].toString()).toUtf8();
        device.write(string);
    }
    // close file
    device.close();

    return true;
}
