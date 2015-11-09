# set files
file (GLOB_RECURSE SUBPROJECT_SOURCES "*.cpp")
file (GLOB_RECURSE SUBPROJECT_HEADERS "*.h" "${PROJECT_CORELIBRARY_DIR}/*h")

# include_path
include_directories ("${PROJECT_CORELIBRARY_DIR}/include"
                     "${CMAKE_CURRENT_BINARY_DIR}"
                     "${CMAKE_BINARY_DIR}"
                     "${Qt_INCLUDE}")

qt5_wrap_cpp (SUBPROJECT_MOC_SOURCES "${SUBPROJECT_HEADERS}")

add_library ("${SUBPROJECT}" SHARED "${SUBPROJECT_SOURCES}" "${SUBPROJECT_HEADERS}"
        "${SUBPROJECT_MOC_SOURCES}")
target_link_libraries ("${SUBPROJECT}" "${Qt_LIBRARIES}")
# install properties
install (TARGETS "${SUBPROJECT}" DESTINATION "${LIB_INSTALL_DIR}")
