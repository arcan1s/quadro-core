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
# @file QuadroConfig.cmake
# Additional file of quadro library
# @author Evgeniy Alekseev
# @copyright GPLv3
# @bug https://github.com/arcan1s/quadro-core/issues
##


##
# @brief try to find quadro libraries
##

##
# @brief optional cmake definitions
##
set(QUADRO_DEFINITIONS "")
##
# @brief path to root include directory
##
find_path(QUADROCORE_INCLUDE_DIR "quadrocore/quadro.h" PATH_SUFFIXES "quadro")
find_path(QUADROUI_INCLUDE_DIR "quadroui/quadroui.h" PATH_SUFFIXES "quadro")
set(QUADRO_INCLUDE_DIRS "${QUADROCORE_INCLUDE_DIR}" "${QUADROUI_INCLUDE_DIR}")
##
# @brief quadro library name
##
find_library(QUADROCORE_LIBRARY NAMES "quadrocore" "libquadrocore"
        PATH_SUFFIXES "quadro")
find_library(QUADROUI_LIBRARY NAMES "quadroui" "libquadroui"
        PATH_SUFFIXES "quadro")
set(QUADRO_LIBRARIES "${QUADROCORE_LIBRARY}" "${QUADROUI_LIBRARY}")
##
# @brief boolean, true if library has been found
##
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Quadro DEFAULT_MSG
        QUADRO_LIBRARIES QUADRO_INCLUDE_DIRS)

##
# @brief additional defined macros
##
include("${CMAKE_CURRENT_LIST_DIR}/QuadroPaths.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/QuadroLibraries.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/QuadroMacros.cmake")
