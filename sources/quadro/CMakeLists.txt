# set project name
set (SUBPROJECT "quadro")
message (STATUS "Subproject ${SUBPROJECT}")

add_subdirectory (src)
file (GLOB SUBPROJECT_DESKTOP *.desktop)
# build man
file (GLOB SUBPROJECT_MAN_IN *.1)
file (RELATIVE_PATH SUBPROJECT_MAN ${CMAKE_SOURCE_DIR} ${SUBPROJECT_MAN_IN})
configure_file (${SUBPROJECT_MAN_IN} ${CMAKE_CURRENT_BINARY_DIR}/${SUBPROJECT_MAN})

install (FILES ${SUBPROJECT_DESKTOP} DESTINATION share/applications/)
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/${SUBPROJECT_MAN} DESTINATION share/man/man1/)
install (FILES bash-completions DESTINATION share/bash-completion/completions/ RENAME ${SUBPROJECT})
install (FILES zsh-completions DESTINATION share/zsh/site-functions/ RENAME _${SUBPROJECT})
