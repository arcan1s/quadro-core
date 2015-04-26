# set files
file (GLOB_RECURSE SOURCES *.cpp ${PROJECT_TRDPARTY_DIR}/task/*.cpp)
file (GLOB_RECURSE HEADERS *.h ${SUBPROJECT_INCLUDE_DIR}/*h
                               ${PROJECT_TRDPARTY_DIR}/task/*.h)

# include_path
include_directories (${SUBPROJECT_INCLUDE_DIR}
                     ${CMAKE_CURRENT_BINARY_DIR}/../
                     ${CMAKE_SOURCE_DIR}
                     ${CMAKE_BINARY_DIR}
                     ${CMAKE_CURRENT_BINARY_DIR}
                     ${PROJECT_TRDPARTY_DIR})

find_package (Qt5 COMPONENTS Core DBus Widgets X11Extras REQUIRED)
add_definitions (${Qt5Core_DEFINITIONS} ${Qt5DBus_DEFINITIONS}
                 ${Qt5Widgets_DEFINITIONS} ${Qt5X11Extras_DEFINITIONS})
include_directories (${Qt5Core_INCLUDE_DIRS} ${Qt5DBus_INCLUDE_DIRS}
                     ${Qt5Widgets_INCLUDE_DIRS} ${Qt5X11Extras_INCLUDE_DIRS})
set (QT_NEEDED_LIBS ${Qt5Core_LIBRARIES} ${Qt5DBus_LIBRARIES}
                    ${Qt5Widgets_LIBRARIES} ${Qt5X11Extras_LIBRARIES})
qt5_wrap_cpp (MOC_SOURCES ${HEADERS})
# x11
find_package (X11)
include_directories (${X11_INCLUDE_DIR})

add_library (${SUBPROJECT} SHARED ${SOURCES} ${HEADERS} ${MOC_SOURCES})
target_link_libraries (${SUBPROJECT} ${QT_NEEDED_LIBS} ${X11_LIBRARIES})
# install properties
install (TARGETS ${SUBPROJECT} DESTINATION lib)
