include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Module definitions
set(MODULE_NAME "WakeIt")

# Define the source files for the plugin
set(
    SRC
    src/backend.cpp
    src/device.cpp
    src/devicemodel.cpp
)

# Create the plugin and set its properties
add_library(WakeItBackend MODULE ${SRC})
set_target_properties(
    WakeItBackend PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${MODULE_NAME}"
)
qt5_use_modules(WakeItBackend Gui Qml Quick)

# Copy the qmldir file to the build dir so that QML code can find the plugin
add_custom_target(
    WakeItBackend-qmldir ALL
    COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/qmldir" "${CMAKE_CURRENT_BINARY_DIR}/${MODULE_NAME}"
    DEPENDS ${QMLFILES}
)

# Install plugin file and qmldir
install(TARGETS WakeItBackend DESTINATION "${QT_IMPORTS_DIR}/${MODULE_NAME}/")
install(FILES "qmldir" DESTINATION "${QT_IMPORTS_DIR}/${MODULE_NAME}/")
