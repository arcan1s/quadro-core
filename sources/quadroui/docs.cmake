# doxygen documentation
find_package (Doxygen)

configure_file (doxygen.conf.in ${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf)
add_custom_target (ui-oxygen-docs ALL COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf)

# html docs
install (DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs/html DESTINATION share/doc/${SUBPROJECT})
