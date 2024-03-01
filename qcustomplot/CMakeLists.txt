cmake_minimum_required(VERSION 3.20)

set(CMAKE_AUTOUIC ON)   # Specific to Qt
set(CMAKE_AUTOMOC ON)   # Specific to Qt
set(CMAKE_AUTORCC ON)   # Specific to Qt

find_package(QT NAMES Qt6 COMPONENTS Core REQUIRED)
find_package(QT NAMES Qt6 COMPONENTS PrintSupport REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS PrintSupport REQUIRED)

file(GLOB PROJECT_SOURCES "*.h" "*.cpp" "*.ui")

add_library(qcustomplot STATIC ${PROJECT_SOURCES})

target_link_libraries(qcustomplot PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(qcustomplot PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)

target_compile_definitions(qcustomplot PUBLIC QCUSTOMPLOT_COMPILE_LIBRARY)

target_include_directories(qcustomplot INTERFACE .)
