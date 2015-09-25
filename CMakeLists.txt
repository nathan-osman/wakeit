project(wakeit CXX)
cmake_minimum_required(VERSION 2.8.9)

# Do not remove this line, its required for the correct functionality of the Ubuntu-SDK
set(UBUNTU_MANIFEST_PATH "manifest.json.in" CACHE INTERNAL "Tells QtCreator location and name of the manifest file")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Qt5Core)
find_package(Qt5Qml)
find_package(Qt5Quick)

# Automatically create moc files
set(CMAKE_AUTOMOC ON)

# Components PATH
execute_process(
    COMMAND dpkg-architecture -qDEB_HOST_MULTIARCH
    OUTPUT_VARIABLE HOST_MULTIARCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Specify the directory for the plugin
set(IMPORTS_DIR "lib/${HOST_MULTIARCH}")

# Project definitions
set(APP_NAME "wakeit")
set(APP_TITLE "Wake It!")
set(APP_DESCRIPTION "Send Wake-on-LAN magic packets")
set(WAKEIT_DIR "share/qml/wakeit")
set(MAIN_QML "${APP_NAME}.qml")
set(APP_ICON "graphics/${APP_NAME}.png")

set(APP_VERSION_MAJOR 0)
set(APP_VERSION_MINOR 1)
set(APP_VERSION_PATCH 4)
set(APP_VERSION "${APP_VERSION_MAJOR}.${APP_VERSION_MINOR}.${APP_VERSION_PATCH}")

# Set install paths
set(CMAKE_INSTALL_PREFIX /)
set(DATA_DIR /)
set(DESKTOP_DIR ${DATA_DIR})
set(APP_DESKTOP "${APP_NAME}.desktop")

set(APP_EXEC "qmlscene $@ ${WAKEIT_DIR}/${MAIN_QML}")

# Determine the name and arch triplet of the host
execute_process(
    COMMAND dpkg-architecture -qDEB_HOST_ARCH
    OUTPUT_VARIABLE HOST_ARCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Configure and set the installation directory for the manifest file
configure_file(manifest.json.in ${CMAKE_CURRENT_BINARY_DIR}/manifest.json)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/manifest.json
        DESTINATION ${CMAKE_INSTALL_PREFIX})

# Install graphics and apparmor profile
install(DIRECTORY "app/graphics" DESTINATION ${DATA_DIR})
install(FILES "${APP_NAME}.apparmor" DESTINATION ${DATA_DIR})

add_subdirectory(app)
add_subdirectory(backend)
add_subdirectory(po)

# Add three custom targets that help with development

add_custom_target(
    "autopilot" chmod +x ${CMAKE_SOURCE_DIR}/app/tests/autopilot/run
    COMMAND ${CMAKE_SOURCE_DIR}/app/tests/autopilot/run
    DEPENDS WakeItBackend WakeItBackend-qmldir
    WORKING_DIRECTORY ./app
)

add_custom_target(
    "check" /usr/bin/qmltestrunner -input ${CMAKE_SOURCE_DIR}/app/tests/unit -import ${CMAKE_BINARY_DIR}/backend
    DEPENDS WakeItBackend WakeItBackend-qmldir
    WORKING_DIRECTORY ./app
)

add_custom_target(
    "run" /usr/bin/qmlscene -I "${CMAKE_BINARY_DIR}/backend" "${CMAKE_SOURCE_DIR}/app/${MAIN_QML}"
    DEPENDS WakeItBackend WakeItBackend-qmldir
    WORKING_DIRECTORY ./app
)

# No-op custom target for click files so that they show up in QtCreator
add_custom_target("click_files" ALL SOURCES "wakeit.apparmor" "manifest.json.in")
