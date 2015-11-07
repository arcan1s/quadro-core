# configure paths
configure_file ("QuadroPaths.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/QuadroPaths.cmake" @ONLY)
# additional files
install (FILES "QuadroConfig.cmake" DESTINATION "${LIB_INSTALL_DIR}/cmake/Quadro")
install (FILES "QuadroLibraries.cmake" DESTINATION "${LIB_INSTALL_DIR}/cmake/Quadro")
install (FILES "QuadroMacros.cmake" DESTINATION "${LIB_INSTALL_DIR}/cmake/Quadro")
install (FILES "${CMAKE_CURRENT_BINARY_DIR}/QuadroPaths.cmake" DESTINATION "${LIB_INSTALL_DIR}/cmake/Quadro")
