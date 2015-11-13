# main qt libraries
find_package(Qt5 5.4.0 REQUIRED COMPONENTS X11Extras)
add_definitions(
        ${Qt5X11Extras_DEFINITIONS}
)
set(Qt_XCB_INCLUDE
        "${Qt_INCLUDE}" "${Qt5X11Extras_INCLUDE_DIRS}"
)
set(Qt_XCB_LIBRARIES
        "${Qt_LIBRARIES}" "${Qt5X11Extras_LIBRARIES}"
)

# x11
find_package(X11)
