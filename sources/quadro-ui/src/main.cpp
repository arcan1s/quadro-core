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
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDir>
#include <QLibraryInfo>
#include <QProcessEnvironment>
#include <QTranslator>
#include <iostream>
#include <unistd.h>

#include <language/language.h>

#include "mainwindow.h"
#include "messages.h"
#include "version.h"


using namespace std;


bool existingSessionOperation(const QString operation)
{
    QDBusConnection bus = QDBusConnection::sessionBus();
    QDBusMessage request = QDBusMessage::createMethodCall(DBUS_SERVICE, DBUS_OBJECT_PATH,
                                                          DBUS_INTERFACE, operation);
    QDBusMessage response = bus.call(request);
    QList<QVariant> arguments = response.arguments();

    return (!arguments.isEmpty() && arguments[0].toBool());
}


int main(int argc, char *argv[])
{
    QVariantMap args = getArgs();
    // reading
    for (int i=1; i<argc; i++) {
    }
    QProcessEnvironment environment = QProcessEnvironment::systemEnvironment();
    QString debugEnv = environment.value(QString("DEBUG"), QString("no"));
    if (!args[QString("debug")].toBool()) args[QString("debug")] = (debugEnv == QString("yes"));
    if ((args[QString("debug")].toBool()) ||
        (args[QString("help")].toBool()) ||
        (args[QString("info")].toBool()) ||
        (args[QString("version")].toBool()) ||
        (args[QString("error")].toBool()))
        args[QString("nodaemon")] = true;

    // detach from console
    if (!args[QString("nodaemon")].toBool())
        daemon(0, 0);
    QApplication a(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);

    // reread translations according to flags
    QString language = Language::defineLanguage(args[QString("config")].toString(),
            args[QString("options")].toString());
    QTranslator qtTranslator;
    qtTranslator.load(QString("qt_%1").arg(language), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);
    QTranslator translator;
    translator.load(QString(":/translations/%1").arg(language));
    a.installTranslator(&translator);

    // running
    if (args[QString("error")].toBool()) {
        cout << errorMessage().toUtf8().data() << endl;
        cout << helpMessage().toUtf8().data();
        return 1;
    } else if (args[QString("help")].toBool()) {
        cout << helpMessage().toUtf8().data();
        return 0;
    } else if (args[QString("info")].toBool()) {
        cout << versionMessage().toUtf8().data() << endl;
        cout << infoMessage().toUtf8().data();
        return 0;
    } else if (args[QString("version")].toBool()) {
        cout << versionMessage().toUtf8().data();
        return 0;
    }

    // check if exists
    if (existingSessionOperation(QString("Active"))) {
        cout << QCoreApplication::translate("MainWindow", "Restore existing session.")
                    .toUtf8().data() << endl;
        existingSessionOperation(QString("Restore"));
        return 0;
    }
    MainWindow w(0, args, &qtTranslator, &translator);
    return a.exec();
}
