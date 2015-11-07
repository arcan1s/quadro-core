# set project name
set (SUBPROJECT "quadrocore")
message (STATUS "Subproject ${SUBPROJECT}")

include("adds.cmake")
add_subdirectory ("src")
# headers
install (DIRECTORY "include/${SUBPROJECT}" DESTINATION "${INCLUDE_INSTALL_DIR}")
# documentation
if (BUILD_DOCS)
    include ("docs.cmake")
endif ()
