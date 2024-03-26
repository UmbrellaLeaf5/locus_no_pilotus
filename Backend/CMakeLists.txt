cmake_minimum_required(VERSION 3.20)

project(backend VERSION 0.1 LANGUAGES CXX)

file(GLOB_RECURSE PROJECT_SOURCES "*.h" "*.cpp")

add_library(backend STATIC ${PROJECT_SOURCES})

include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake_paths.cmake")
include(${CMAKESCRIPTS_DIR}/scripts_for_vscode.cmake)
add_qt_runtime(${CMAKE_CURRENT_SOURCE_DIR} backend)