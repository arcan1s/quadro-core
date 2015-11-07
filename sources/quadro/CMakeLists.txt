# set project name
set (SUBPROJECT "quadro")
message (STATUS "Subproject ${SUBPROJECT}")

add_subdirectory ("src")
file (GLOB SUBPROJECT_DESKTOP "*.desktop")
# build man
file (GLOB SUBPROJECT_MAN_IN "*.1")
file (RELATIVE_PATH SUBPROJECT_MAN "${CMAKE_SOURCE_DIR}" "${SUBPROJECT_MAN_IN}")
configure_file ("${SUBPROJECT_MAN_IN}" "${CMAKE_CURRENT_BINARY_DIR}/${SUBPROJECT_MAN}")

install (FILES "${SUBPROJECT_DESKTOP}" DESTINATION "${DATA_INSTALL_DIR}/applications")
install (FILES "${CMAKE_CURRENT_BINARY_DIR}/${SUBPROJECT_MAN}" DESTINATION "${DATA_INSTALL_DIR}/man/man1")
install (FILES "bash-completions" DESTINATION "${DATA_INSTALL_DIR}/bash-completion/completions" RENAME "${SUBPROJECT}")
install (FILES "zsh-completions" DESTINATION "${DATA_INSTALL_DIR}/zsh/site-functions" RENAME "_${SUBPROJECT}")
