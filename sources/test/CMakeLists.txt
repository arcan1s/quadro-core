# set project name
set (SUBPROJECT "quadro-test")
message (STATUS "Subproject ${SUBPROJECT}")

# set files
# set (NETCTL_HEADERS testnetctl.h)
# set (NETCTL_SOURCES testnetctl.cpp ${PROJECT_TRDPARTY_DIR}/listmap/listmap.cpp)

# include_path
include_directories ("${PROJECT_CORELIBRARY_DIR}/include"
                     "${PROJECT_UILIBRARY_DIR}/include"
                     ${CMAKE_CURRENT_BINARY_DIR}
                     ${CMAKE_BINARY_DIR})

# qt5_wrap_cpp (NETCTL_MOC_SOURCES ${NETCTL_HEADERS})

# add_executable (${SUBPROJECT}-netctl ${NETCTL_HEADERS} ${NETCTL_SOURCES} ${NETCTL_MOC_SOURCES})
# target_link_libraries (${SUBPROJECT}-netctl ${PROJECT_NAME} ${QT_NEEDED_LIBS})

# install properties
add_test (NAME Main COMMAND "${CMAKE_CURRENT_BINARY_DIR}/${SUBPROJECT}-main"
          "-o" "../Testing/output-test.log")

