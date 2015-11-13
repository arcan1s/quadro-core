# set project name
set (SUBPROJECT "quadroxcbadaptor")
message (STATUS "Subproject ${SUBPROJECT}")

# set files
file (GLOB_RECURSE SUBPROJECT_SOURCES "*.cpp")
file (GLOB_RECURSE SUBPROJECT_HEADERS "*.h")

# include_path
include("libraries.cmake")
include_directories ("${PROJECT_CORELIBRARY_DIR}/include"
                     "${CMAKE_CURRENT_BINARY_DIR}"
                     "${CMAKE_BINARY_DIR}"
                     "${X11_INCLUDE_DIR}"
                     "${Qt_XCB_INCLUDE}")

qt5_wrap_cpp (SUBPROJECT_MOC_SOURCES "${SUBPROJECT_HEADERS}")

add_library ("${SUBPROJECT}" MODULE "${SUBPROJECT_SOURCES}" "${SUBPROJECT_HEADERS}"
        "${SUBPROJECT_MOC_SOURCES}")
target_link_libraries ("${SUBPROJECT}" "${Qt_XCB_LIBRARIES}" "${X11_LIBRARIES}")
# install properties
install (TARGETS "${SUBPROJECT}" DESTINATION "${LIB_INSTALL_DIR}")
