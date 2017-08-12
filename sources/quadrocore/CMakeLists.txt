# set project name
set (SUBPROJECT "quadrocore")
message (STATUS "Subproject ${SUBPROJECT}")

configure_file ("Config.h.in" "${CMAKE_BINARY_DIR}/Config.h")

include("adds.cmake")
add_subdirectory ("src")
# headers
install (DIRECTORY "include/${SUBPROJECT}" DESTINATION "${INCLUDE_INSTALL_DIR}")
install (FILES "${CMAKE_BINARY_DIR}/config.h" DESTINATION "${INCLUDE_INSTALL_DIR}/${SUBPROJECT}")
# documentation
if (BUILD_DOCS)
    include ("docs.cmake")
endif ()
