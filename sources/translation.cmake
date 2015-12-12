file (GLOB_RECURSE PROJECT_TS "${PROJECT_RESOURCE_DIR}/*.ts")
if (UPDATE_TRANSLATIONS)
    qt5_create_translation (PROJECT_QM "${CMAKE_CURRENT_BINARY_DIR}"
            "${CMAKE_CURRENT_SOURCE_DIR}" ${PROJECT_TS})
else ()
    qt5_add_translation(PROJECT_QM ${PROJECT_TS})
endif ()

add_custom_target (translations ALL DEPENDS ${PROJECT_QM})
install(FILES ${PROJECT_QM} DESTINATION "${DATA_INSTALL_DIR}/quadro/translations")
