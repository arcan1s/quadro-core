# set project name
set (SUBPROJECT quadro-test)
message (STATUS "Subproject ${SUBPROJECT}")

# set directories
set (SUBPROJECT_BINARY_DIR bin)

# additional targets
set (TARGETS "")

# set files
# set (NETCTL_HEADERS testnetctl.h)
# set (NETCTL_SOURCES testnetctl.cpp ${PROJECT_TRDPARTY_DIR}/listmap/listmap.cpp)

# include_path
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/../${PROJECT_NAME}/include/
                     ${CMAKE_CURRENT_BINARY_DIR}/../
                     ${CMAKE_SOURCE_DIR}
                     ${CMAKE_BINARY_DIR}
                     ${CMAKE_CURRENT_BINARY_DIR}
                     ${PROJECT_TRDPARTY_DIR})
link_directories (${PROJECT_NAME}/src/lib)

find_package (Qt5 COMPONENTS Core DBus Test REQUIRED)
add_definitions (${Qt5Core_DEFINITIONS} ${Qt5DBus_DEFINITIONS} ${Qt5Test_DEFINITIONS})
include_directories (${Qt5Core_INCLUDE_DIRS} ${Qt5DBus_INCLUDE_DIRS} ${Qt5Test_INCLUDE_DIRS})
set (QT_NEEDED_LIBS ${Qt5Core_LIBRARIES} ${Qt5DBus_LIBRARIES} ${Qt5Test_LIBRARIES})
#   qt5_wrap_cpp (NETCTL_MOC_SOURCES ${NETCTL_HEADERS})

# add_executable (${SUBPROJECT}-netctl ${NETCTL_HEADERS} ${NETCTL_SOURCES} ${NETCTL_MOC_SOURCES})
# target_link_libraries (${SUBPROJECT}-netctl ${PROJECT_NAME} ${QT_NEEDED_LIBS})

# install properties
add_test (NAME Main COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${SUBPROJECT}-main
          "-o" "../Testing/output-test.log")

