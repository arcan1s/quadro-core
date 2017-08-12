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


#include <QApplication>
#include <QCommandLineParser>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDir>
#include <QLibraryInfo>
#include <QTranslator>
#include <iostream>
#include <unistd.h>

#include <quadrocore/Quadro.h>

#include "QuadroMainWindow.h"
#include "version.h"

using namespace Quadro;


bool existingSessionOperation(const QString _operation)
{
    QDBusConnection bus = QDBusConnection::sessionBus();
    QDBusMessage request = QDBusMessage::createMethodCall(
        DBUS_SERVICE, DBUS_UI_OBJECT_PATH, DBUS_INTERFACE, _operation);
    QDBusMessage response = bus.call(request);
    QList<QVariant> arguments = response.arguments();

    return (!arguments.isEmpty() && arguments.at(0).type() == QVariant::Bool
            && arguments[0].toBool());
}


void loadTranslator(QApplication &_app)
{
    // qt specific
    bool trStatus;
    static QTranslator qtTranslator;
    trStatus = qtTranslator.load(
        QString("qt_%1").arg(QLocale::system().name()),
        QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    qCDebug(LOG_UI) << "Loading Qt specific translation" << trStatus;
    trStatus = _app.installTranslator(&qtTranslator);
    qCDebug(LOG_UI) << "Install Qt translator" << trStatus;
    // application specific
    static QTranslator translator;
    trStatus = translator.load(
        QString("core-quadro_%1").arg(QLocale::system().name()),
        QString("%1/%2/%3/%4")
            .arg(ROOT_INSTALL_DIR)
            .arg(DATA_INSTALL_DIR)
            .arg(HOME_PATH)
            .arg(TRANSLATION_PATH));
    qCDebug(LOG_UI) << "Loading application specific translation" << trStatus;
    trStatus = _app.installTranslator(&translator);
    qCDebug(LOG_UI) << "Install application translator" << trStatus;
}


int main(int argc, char *argv[])
{
    // daemon(0, 0);

    QApplication app(argc, argv);
    app.setApplicationName(NAME);
    app.setApplicationVersion(VERSION);
    QApplication::setQuitOnLastWindowClosed(false);

    // parser
    QCommandLineParser parser;
    parser.setApplicationDescription(QApplication::translate(
        "MainWindow", "Plugin based applicaiton launcher"));
    parser.addHelpOption();
    parser.addVersionOption();
    // debug mode
    QCommandLineOption debugOption(
        {"d", "debug"},
        QApplication::translate("MainWindow", "Print debug information"));
    parser.addOption(debugOption);
    // minimized
    QCommandLineOption minimizedOption(
        "minimized",
        QApplication::translate("MainWindow", "Start minimized to tray"));
    parser.addOption(minimizedOption);
    parser.process(app);

    // enable debug
    if (parser.isSet(debugOption))
        QuadroDebug::enableDebug();

    loadTranslator(app);

    // check if exists
    if (existingSessionOperation("Active")) {
        std::cout << QApplication::translate("MainWindow",
                                             "Restore existing session")
                         .toUtf8()
                         .data()
                  << std::endl;
        existingSessionOperation("Restore");
        return 0;
    }
    QuadroMainWindow w(nullptr, QVariantHash());
    return app.exec();
}
