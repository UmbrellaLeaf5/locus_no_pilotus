cmake_minimum_required(VERSION 3.20)

project(gui VERSION 0.1 LANGUAGES CXX)

file(GLOB_RECURSE PROJECT_SOURCES "*.h" "*.cpp")

add_library(gui STATIC ${PROJECT_SOURCES})

target_link_libraries(gui PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(gui PRIVATE QCUSTOMPLOT_USE_LIBRARY)
target_link_libraries(gui PUBLIC qcustomplot)

include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake_paths.cmake")
include(${CMAKESCRIPTS_DIR}/scripts_for_vscode.cmake)
add_qt_runtime(${CMAKE_CURRENT_SOURCE_DIR} gui)
