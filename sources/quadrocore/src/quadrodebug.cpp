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
 * @file quadrodebug.cpp
 * Source code of quadro library
 * @author Evgeniy Alekseev
 * @copyright GPLv3
 * @bug https://github.com/arcan1s/quadro-core/issues
 */


#include "quadro/quadro.h"

#include "version.h"


Q_LOGGING_CATEGORY(LOG_DBUS, "core.quadro.dbus", QtMsgType::QtWarningMsg)
Q_LOGGING_CATEGORY(LOG_LIB, "core.quadro.library", QtMsgType::QtWarningMsg)
Q_LOGGING_CATEGORY(LOG_PL, "core.quadro.plugin", QtMsgType::QtWarningMsg)
Q_LOGGING_CATEGORY(LOG_UI, "core.quadro.ui", QtMsgType::QtWarningMsg)
Q_LOGGING_CATEGORY(LOG_UILIB, "core.quadro.uilibrary", QtMsgType::QtWarningMsg)


/**
 * @fn getBuildData
 */
const QStringList getBuildData()
{
    QStringList metadata;
    metadata.append(QString("=== Quadro configuration details ==="));
    // build information
    metadata.append(QString("Build details:"));
    metadata.append(QString("    VERSION: %1").arg(VERSION));
    metadata.append(QString("    COMMIT_SHA: %1").arg(COMMIT_SHA));
    metadata.append(QString("    BUILD_DATE: %1").arg(BUILD_DATE));
    // cmake properties
    metadata.append(QString("cmake properties:"));
    metadata.append(QString("    CMAKE_BUILD_TYPE: %1").arg(CMAKE_BUILD_TYPE));
    metadata.append(
        QString("    CMAKE_CXX_COMPILER: %1").arg(CMAKE_CXX_COMPILER));
    metadata.append(QString("    CMAKE_CXX_FLAGS: %1").arg(CMAKE_CXX_FLAGS));
    metadata.append(
        QString("    CMAKE_CXX_FLAGS_DEBUG: %1").arg(CMAKE_CXX_FLAGS_DEBUG));
    metadata.append(QString("    CMAKE_CXX_FLAGS_RELEASE: %1")
                        .arg(CMAKE_CXX_FLAGS_RELEASE));
    metadata.append(QString("    CMAKE_CXX_FLAGS_OPTIMIZATION: %1")
                        .arg(CMAKE_CXX_FLAGS_OPTIMIZATION));
    metadata.append(
        QString("    CMAKE_DEFINITIONS: %1").arg(CMAKE_DEFINITIONS));
    metadata.append(
        QString("    CMAKE_INSTALL_PREFIX: %1").arg(CMAKE_INSTALL_PREFIX));
    metadata.append(QString("    CMAKE_SHARED_LINKER_FLAGS: %1")
                        .arg(CMAKE_SHARED_LINKER_FLAGS));
    // components
    metadata.append(QString("Components data:"));
    metadata.append(
        QString("    BUILD_DEB_PACKAGE: %1").arg(BUILD_DEB_PACKAGE));
    metadata.append(
        QString("    BUILD_RPM_PACKAGE: %1").arg(BUILD_RPM_PACKAGE));
    metadata.append(
        QString("    CLANGFORMAT_EXECUTABLE: %1").arg(CLANGFORMAT_EXECUTABLE));
    metadata.append(
        QString("    CPPCHECK_EXECUTABLE: %1").arg(CPPCHECK_EXECUTABLE));
    metadata.append(QString("    PROP_DOCS: %1").arg(PROP_DOCS));
    metadata.append(QString("    PROP_TEST: %1").arg(PROP_TEST));

    return metadata;
}
