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
# @file QuadroLibraries.cmake
# Additional file of quadro library
# @author Evgeniy Alekseev
# @copyright GPLv3
# @bug https://github.com/arcan1s/quadro-core/issues
##


##
# @brief Quadro common libraries
##

find_package(Qt5 5.4.0 REQUIRED COMPONENTS Core DBus Widgets)
##
# @brief add Qt definitions
##
add_definitions(
        ${Qt5Core_DEFINITIONS} ${Qt5DBus_DEFINITIONS} ${Qt5Widgets_DEFINITIONS}
)
##
# @def Qt_INCLUDE
# Qt include paths
##
set(Qt_INCLUDE
        "${Qt5Core_INCLUDE_DIRS}" "${Qt5DBus_INCLUDE_DIRS}" "${Qt5Widgets_INCLUDE_DIRS}"
)
##
# @def Qt_LIBRARIES
# Qt libraries
##
set(Qt_LIBRARIES
        "${Qt5Core_LIBRARIES}" "${Qt5DBus_LIBRARIES}" "${Qt5Widgets_LIBRARIES}"
)
