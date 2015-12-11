file (GLOB_RECURSE PROJECT_TS "${PROJECT_RESOURCE_DIR}/*.ts")
file(GLOB_RECURSE ALL_SOURCE_FILES "*.cpp" "*.h")
foreach (SOURCE_FILE ${ALL_SOURCE_FILES})
    string(FIND "${SOURCE_FILE}" "${PROJECT_TRDPARTY_DIR}" PROJECT_TRDPARTY_DIR_FOUND)
    if (NOT "${PROJECT_TRDPARTY_DIR_FOUND}" EQUAL "-1")
        list(REMOVE_ITEM ALL_SOURCE_FILES "${SOURCE_FILE}")
    endif ()
endforeach ()
file(GLOB_RECURSE ALL_UI_HEADERS "${CMAKE_CURRENT_BINARY_DIR}/*.h")

if (UPDATE_TRANSLATIONS)
    qt5_create_translation (PROJECT_QM ${ALL_SOURCE_FILES} ${ALL_UI_HEADERS}
            ${PROJECT_TS})
else ()
    qt5_add_translation(PROJECT_QM ${PROJECT_TS})
endif ()

add_custom_target (translations ALL DEPENDS ${PROJECT_QM})
install(FILES ${PROJECT_QM} DESTINATION "${DATA_INSTALL_DIR}/quadro/translations")
