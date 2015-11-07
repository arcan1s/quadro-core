# set project name
set (SUBPROJECT "quadro-resources")
message (STATUS "Subproject ${SUBPROJECT}")

install (FILES "icon.png" DESTINATION "${DATA_INSTALL_DIR}/pixmaps" RENAME "quadro.png")
