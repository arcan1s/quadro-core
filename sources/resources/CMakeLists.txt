# set project name
set (SUBPROJECT quadro-resources)
message (STATUS "Subproject ${SUBPROJECT}")

install (FILES icon.png DESTINATION share/pixmaps RENAME quadro.png)
