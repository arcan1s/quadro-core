# set files
file (GLOB_RECURSE SOURCES *.cpp ${PROJECT_TRDPARTY_DIR}/task/*.cpp)
file (GLOB_RECURSE HEADERS *.h ${SUBPROJECT_INCLUDE_DIR}/*h
                               ${PROJECT_TRDPARTY_DIR}/task/*.h)

# include_path
include_directories (${SUBPROJECT_INCLUDE_DIR}
                     ${CMAKE_SOURCE_DIR}
                     ${CMAKE_BINARY_DIR}
                     ${CMAKE_CURRENT_BINARY_DIR}
                     ${PROJECT_TRDPARTY_DIR}
                     ${Qt_INCLUDE}
                     ${X11_INCLUDE})

# qt5_wrap_cpp (MOC_SOURCES ${HEADERS})

add_library (${SUBPROJECT} SHARED ${SOURCES} ${HEADERS} ${MOC_SOURCES})
target_link_libraries (${SUBPROJECT} ${Qt_LIBRARIES} ${X11_LIBRARIES})
# install properties
install (TARGETS ${SUBPROJECT} DESTINATION lib)
