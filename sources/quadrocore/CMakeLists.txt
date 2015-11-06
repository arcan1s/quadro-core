# set project name
set (SUBPROJECT "quadrocore")
message (STATUS "Subproject ${SUBPROJECT}")

add_subdirectory (src)
# headers
install (DIRECTORY include/${PROJECT_NAME} DESTINATION include/)
# additional files
install (FILES "QuadroConfig.cmake" DESTINATION lib/cmake/Quadro)
install (FILES "QuadroMacros.cmake" DESTINATION lib/cmake/Quadro)
install (FILES "QuadroLibraries.cmake" DESTINATION lib/cmake/Quadro)
# documentation
if (BUILD_DOCS)
    include (docs.cmake)
endif ()
