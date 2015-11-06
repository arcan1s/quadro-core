# set project name
set (SUBPROJECT "quadroui")
message (STATUS "Subproject ${SUBPROJECT}")

add_subdirectory (src)
# headers
install (DIRECTORY include/${SUBPROJECT} DESTINATION include/)
# documentation
if (BUILD_DOCS)
    include (docs.cmake)
endif ()
