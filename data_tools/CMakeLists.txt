cmake_minimum_required(VERSION 3.20)

project(data_tools VERSION 0.1 LANGUAGES CXX)

file(GLOB_RECURSE PROJECT_SOURCES "*.h" "*.cpp")

add_library(data_tools STATIC ${PROJECT_SOURCES})

target_link_libraries(data_tools PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core)

target_link_libraries(data_tools PRIVATE lib)
target_link_libraries(data_tools PRIVATE gui)

target_compile_definitions(data_tools PRIVATE QCUSTOMPLOT_USE_LIBRARY)
target_link_libraries(data_tools PUBLIC qcustomplot)

include(${CMAKESCRIPTS_DIR}/scripts_for_vscode.cmake)
add_qt_runtime(${CMAKE_CURRENT_SOURCE_DIR} data_tools)

find_package(IcecreamCpp)
include_directories(${IcecreamCpp_INCLUDE_DIRS})