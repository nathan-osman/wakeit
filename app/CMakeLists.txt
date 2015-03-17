# Find all of the QML and JS files
file(GLOB QML_JS_FILES *.qml *.js)

# Configure the .desktop.in file
configure_file("${APP_DESKTOP}.in" "${CMAKE_CURRENT_BINARY_DIR}/${APP_DESKTOP}.in")

# Install the .desktop and QML files
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${APP_DESKTOP}" DESTINATION "${DATA_DIR}")
install(FILES "${QML_JS_FILES}" DESTINATION "${APP_DIR}")

# No-op custom target for QML and JS files so that they show up in QtCreator
add_custom_target("qml_and_js_files" ALL SOURCES ${QML_JS_FILES})
