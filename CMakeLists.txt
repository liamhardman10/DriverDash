cmake_minimum_required(VERSION 3.21)

project(DriverDash
    VERSION 0.1.0
    DESCRIPTION "An open head-unit interface"
    LANGUAGES CXX
)

# ---------------------------------------------------------------------------
# C++ standard
# ---------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---------------------------------------------------------------------------
# Qt discovery
# ---------------------------------------------------------------------------
find_package(Qt6 6.5 REQUIRED COMPONENTS
    Core
    Gui
    Qml
    Quick
    QuickControls2
)

qt_standard_project_setup(REQUIRES 6.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---------------------------------------------------------------------------
# Platform selection
#   Default: desktop. Later, build for Pi with -DDRIVERDASH_PLATFORM=pi
# ---------------------------------------------------------------------------
set(DRIVERDASH_PLATFORM "desktop" CACHE STRING "Target platform (desktop|pi)")
set_property(CACHE DRIVERDASH_PLATFORM PROPERTY STRINGS desktop pi)

if(DRIVERDASH_PLATFORM STREQUAL "pi")
    add_compile_definitions(DRIVERDASH_PLATFORM_PI)
else()
    add_compile_definitions(DRIVERDASH_PLATFORM_DESKTOP)
endif()

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------
set(DRIVERDASH_SOURCES
    src/main.cpp
    src/AppController.cpp
    src/AppController.h
)

# ---------------------------------------------------------------------------
# Executable
# ---------------------------------------------------------------------------
qt_add_executable(driverdash
    ${DRIVERDASH_SOURCES}
)

# ---------------------------------------------------------------------------
# QML module
#   All .qml files under qml/ get compiled into the binary as a Qt resource.
#   The URI (DriverDash) is what QML imports with `import DriverDash`.
# ---------------------------------------------------------------------------
qt_add_qml_module(driverdash
    URI DriverDash
    VERSION 1.0
    QML_FILES
        qml/Main.qml
)

# ---------------------------------------------------------------------------
# Link libraries
# ---------------------------------------------------------------------------
target_link_libraries(driverdash PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
)

# ---------------------------------------------------------------------------
# Include paths
# ---------------------------------------------------------------------------
target_include_directories(driverdash PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# ---------------------------------------------------------------------------
# Platform-specific bits
# ---------------------------------------------------------------------------
if(DRIVERDASH_PLATFORM STREQUAL "pi")
    # EGLFS: render directly to DRM/KMS, no compositor.
    # Only applied when actually building for the Pi.
    target_compile_definitions(driverdash PRIVATE
        QT_QPA_PLATFORM_DEFAULT="eglfs"
    )
endif()

# ---------------------------------------------------------------------------
# Install rules
# ---------------------------------------------------------------------------
include(GNUInstallDirs)

install(TARGETS driverdash
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Qt 6.5+ helper: installs the QML module alongside the binary
qt_generate_deploy_qml_app_script(
    TARGET driverdash
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})