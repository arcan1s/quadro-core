cmake_minimum_required (VERSION 2.8.12)

cmake_policy (SET CMP0003 OLD)
cmake_policy (SET CMP0002 OLD)
cmake_policy (SET CMP0011 NEW)
cmake_policy (SET CMP0015 NEW)

project ("quadro")
set (PROJECT_AUTHOR "Evgeniy Alekseev")
set (PROJECT_CONTACT "esalexeev@gmail.com")
set (PROJECT_LICENSE "GPLv3")
set (PROJECT_VERSION_MAJOR "0")
set (PROJECT_VERSION_MINOR "9")
set (PROJECT_VERSION_PATCH "0")
set (PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
# append git version if any
set(PROJECT_COMMIT_SHA "" CACHE INTERNAL "Commit hash")
include("checkgit.cmake")

string (TIMESTAMP CURRENT_DATE "%Y-%m-%d %H:%M" UTC)
string (TIMESTAMP CURRENT_YEAR "%Y")

message (STATUS "Project: ${PROJECT_NAME}")
message (STATUS "Version: ${PROJECT_VERSION}")
message (STATUS "Build date: ${CURRENT_DATE}")

# paths
set(BIN_INSTALL_DIR "bin" CACHE STRING "Installation directory for executables")
set(DATA_INSTALL_DIR "share" CACHE STRING "Installation directory for data")
set(INCLUDE_INSTALL_DIR "include" CACHE STRING "Installation directory for headers")
set(LIB_INSTALL_DIR "lib" CACHE STRING "Installation directory for libraries")
# components
option(BUILD_DEB_PACKAGE "Build deb package" OFF)
option(BUILD_RPM_PACKAGE "Build rpm package" OFF)
option(ENABLE_WAYLAND_SUPPORT "Build wayland plugin" ON)
option(ENABLE_XCB_SUPPORT "Build X11 plugin" ON)
# install options
option (BUILD_DOCS "Build Doxygen documentation" OFF)
option (BUILD_TESTING "Build unit tests" OFF)
# some additional targets
set(CLANGFORMAT_EXECUTABLE "/usr/bin/clang-format" CACHE STRING "Path to clang-format executable")
set(CPPCHECK_EXECUTABLE "/usr/bin/cppcheck" CACHE STRING "Path to cppcheck executable")

# flags
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-Wall -Wno-cpp -std=c++11")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_OPTIMIZATION "-Ofast -DNDEBUG")
    # avoid newer gcc warnings
    add_definitions(-D_DEFAULT_SOURCE)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -stdlib=libc++")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_OPTIMIZATION "-Ofast -DNDEBUG")
    # linker flags
    set(CMAKE_EXE_LINKER_FLAGS "-lc++abi")
    set(CMAKE_MODULE_LINKER_FLAGS "-lc++abi")
    set(CMAKE_SHARED_LINKER_FLAGS "-lc++abi")
else ()
    message(FATAL_ERROR "Unknown compiler")
endif ()
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif ()

set(PROJECT_TRDPARTY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty")
set(PROJECT_RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")
include("libraries.cmake")
include("clang-format.cmake")
include("cppcheck.cmake")
include("translation.cmake")

# libraries configuration
set(PROJECT_CORELIBRARY "quadrocore")
set(PROJECT_CORELIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_CORELIBRARY}")
set(PROJECT_UILIBRARY "quadroui")
set(PROJECT_UILIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_UILIBRARY}")

get_directory_property(CMAKE_DEFINITIONS COMPILE_DEFINITIONS)
configure_file ("${CMAKE_SOURCE_DIR}/version.h.in" "${CMAKE_CURRENT_BINARY_DIR}/version.h")
add_subdirectory ("${PROJECT_RESOURCE_DIR}")
add_subdirectory ("quadrocore")
add_subdirectory ("quadroui")
add_subdirectory ("quadrodesktopadaptors")
add_subdirectory ("quadro")
if (BUILD_TESTING)
    enable_testing ()
    add_subdirectory ("test")
endif ()

include("packages-recipe.cmake")
