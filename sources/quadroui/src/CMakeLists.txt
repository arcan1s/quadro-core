# set files
file (GLOB_RECURSE SUBPROJECT_SOURCES "*.cpp" "${PROJECT_TRDPARTY_DIR}/flowlayout/flowlayout.cpp")
file (GLOB_RECURSE SUBPROJECT_HEADERS "${PROJECT_UILIBRARY_DIR}/*h"
                                      "${PROJECT_TRDPARTY_DIR}/flowlayout/flowlayout.h")
file (GLOB_RECURSE SUBPROJECT_FORMS "*.ui")
set (SUBPROJECT_RESOURCES "${PROJECT_RESOURCE_DIR}/${SUBPROJECT}.qrc")

# include_path
include_directories ("${PROJECT_CORELIBRARY_DIR}/include"
                     "${PROJECT_UILIBRARY_DIR}/include"
                     "${CMAKE_CURRENT_BINARY_DIR}"
                     "${CMAKE_BINARY_DIR}"
                     "${PROJECT_TRDPARTY_DIR}"
                     "${Qt_INCLUDE}")

qt5_wrap_cpp (SUBPROJECT_MOC_SOURCES "${SUBPROJECT_HEADERS}")
qt5_wrap_ui (SUBPROJECT_UI_HEADERS "${SUBPROJECT_FORMS}")
qt5_add_resources (SUBPROJECT_QRC_SOURCES "${SUBPROJECT_RESOURCES}")

add_library ("${SUBPROJECT}" SHARED "${SUBPROJECT_SOURCES}" "${SUBPROJECT_HEADERS}"
        "${SUBPROJECT_MOC_SOURCES}" "${SUBPROJECT_UI_HEADERS}" "${SUBPROJECT_QRC_SOURCES}")
target_link_libraries ("${SUBPROJECT}" "${Qt_LIBRARIES}" "${PROJECT_CORELIBRARY}")
# install properties
install (TARGETS "${SUBPROJECT}" DESTINATION "${LIB_INSTALL_DIR}")
