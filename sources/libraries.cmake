# main qt libraries
find_package(Qt5 5.4.0 REQUIRED COMPONENTS Core DBus LinguistTools Test Widgets X11Extras)
add_definitions(
        ${Qt5Core_DEFINITIONS} ${Qt5DBus_DEFINITIONS} ${Qt5LinguistTools_DEFINITIONS}
        ${Qt5Test_DEFINITIONS} ${Qt5Widgets_DEFINITIONS} ${Qt5X11Extras_DEFINITIONS}
)
set(Qt_INCLUDE
        "${Qt5Core_INCLUDE_DIRS}" "${Qt5DBus_INCLUDE_DIRS}" "${${Qt5Test_INCLUDE_DIRS}}"
        "${Qt5Widgets_INCLUDE_DIRS}" "${Qt5X11Extras_INCLUDE_DIRS}"
)
set(Qt_LIBRARIES
        "${Qt5Core_LIBRARIES}" "${Qt5DBus_LIBRARIES}" "${Qt5Test_LIBRARIES}"
        "${Qt5Widgets_LIBRARIES}" "${Qt5X11Extras_LIBRARIES}"
)

# x11
find_package(X11)
set(X11_INCLUDE
        "${X11_INCLUDE_DIR}"
)
set(X11_LIBRARIES
        "${X11_LIBRARIES}"
)
