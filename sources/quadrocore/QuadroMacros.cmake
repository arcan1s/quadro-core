###########################################################################
#   This file is part of quadro                                           #
#                                                                         #
#   quadro is free software: you can redistribute it and/or               #
#   modify it under the terms of the GNU General Public License as        #
#   published by the Free Software Foundation, either version 3 of the    #
#   License, or (at your option) any later version.                       #
#                                                                         #
#   quadro is distributed in the hope that it will be useful,             #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of        #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
#   GNU General Public License for more details.                          #
#                                                                         #
#   You should have received a copy of the GNU General Public License     #
#   along with quadro. If not, see http://www.gnu.org/licenses/           #
###########################################################################
##
# @file QuadroMacros.cmake
# Additional file of quadro library
# @author Evgeniy Alekseev
# @copyright GPLv3
# @bug https://github.com/arcan1s/quadro-core/issues
##


##
# @brief additional macros for quadro core
##

##
# @fn quadro_install_plugin root [name] [libraries]
# @brief build and install plugin
# @param PLUGIN_ROOT         plugin root directory
# @param PLUGIN              plugin name (optional). Will be assigned from path
#                            if empty
# @param ADDS_LIBRARIES      additional libraries (optional)
#
##
macro(quadro_install_plugin PLUGIN_ROOT)
    set(PLUGIN "${ARGV1}")
    if (NOT PLUGIN)
        set(PLUGIN "${PLUGIN_ROOT}")
    endif()
    set(ADDS_LIBRARIES "${ARGV2}")
    message (STATUS "Plugin ${PLUGIN}")
    # get sources
    file (GLOB_RECURSE ${PLUGIN}_SOURCES "${PLUGIN_ROOT}/*.cpp")
    file (GLOB_RECURSE ${PLUGIN}_HEADERS "${PLUGIN_ROOT}/*.h")
    file (GLOB_RECURSE ${PLUGIN}_FORMS "${PLUGIN_ROOT}/*.ui")
    qt5_wrap_cpp (${PLUGIN}_MOC_SOURCES "${${PLUGIN}_HEADERS}")
    if (${${PLUGIN}_FORMS})
        qt5_wrap_ui (${PLUGIN}_UI_HEADERS "${${PLUGIN}_FORMS}")
    endif()

    # include directories
    include_directories ("${CMAKE_CURRENT_BINARY_DIR}"
                         "${Qt_INCLUDE}"
                         "${QUADRO_INCLUDE_DIRS}")

    # build
    add_library ("${PLUGIN}" MODULE "${${PLUGIN}_SOURCES}" "${${PLUGIN}_HEADERS}"
            "${${PLUGIN}_MOC_SOURCES}" "${${PLUGIN}_UI_HEADERS}")
    target_link_libraries ("${PLUGIN}" "${QUADRO_LIBRARIES}" "${Qt_LIBRARIES}" "${ADDS_LIBRARIES}")

    # install
    install (TARGETS "${PLUGIN}" DESTINATION "${QUADRO_PLUGIN_ROOT}")
    install (FILES "${PLUGIN_ROOT}/${PLUGIN}.desktop" DESTINATION "${QUADRO_PLUGIN_ROOT}"
            RENAME "core.quadro.${PLUGIN}.desktop")
endmacro()
