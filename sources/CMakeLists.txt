cmake_minimum_required (VERSION 2.8.12)

cmake_policy (SET CMP0003 OLD)
cmake_policy (SET CMP0002 OLD)
cmake_policy (SET CMP0011 NEW)
cmake_policy (SET CMP0015 NEW)

project (quadro-core)
set (PROJECT_AUTHOR "Evgeniy Alekseev")
set (PROJECT_CONTACT "esalexeev@gmail.com")
set (PROJECT_LICENSE "GPLv3")
set (PROJECT_VERSION_MAJOR 0)
set (PROJECT_VERSION_MINOR 9)
set (PROJECT_VERSION_PATCH 0)
set (PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
string (TIMESTAMP CURRENT_DATE "%Y-%m-%d %H:%M" UTC)
string (TIMESTAMP CURRENT_YEAR "%Y")

message (STATUS "Project: ${PROJECT_NAME}")
message (STATUS "Version: ${PROJECT_VERSION}")
message (STATUS "Build date: ${CURRENT_DATE}")

# install options
option (BUILD_DOCS "Build Doxygen documentation" OFF)
option (BUILD_TEST "Build unit tests" OFF)

# flags
if (CMAKE_COMPILER_IS_GNUCXX)
  set (CMAKE_CXX_FLAGS "-Wall -std=c++11")
  set (CMAKE_CXX_FLAGS_DEBUG "-g -O0")
  set (CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
  # avoid newer gcc warnings
  add_definitions (-D_DEFAULT_SOURCE)
else ()
  message (STATUS "Unsupported compiler")
endif ()

configure_file (${CMAKE_SOURCE_DIR}/version.h.in ${CMAKE_CURRENT_BINARY_DIR}/version.h)

# resources
set (PROJECT_TRDPARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty)
set (PROJECT_RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
add_subdirectory (${PROJECT_RESOURCE_DIR})

# components
add_subdirectory (quadro-core)
add_subdirectory (quadro-ui)
if (BUILD_TEST)
  enable_testing ()
  add_subdirectory (test)
endif ()
