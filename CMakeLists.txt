cmake_minimum_required(VERSION 3.20)

project(locus_no_pilotus)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core PrintSupport REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core PrintSupport REQUIRED)

set(Boost_USE_STATIC_LIBS OFF)

find_package(Boost REQUIRED COMPONENTS locale unit_test_framework)

# add images to build directory
file(COPY ${CMAKE_SOURCE_DIR}/images DESTINATION ${CMAKE_BINARY_DIR})

cmake_path(SET QCUSTOMPLOT_DIR "${CMAKE_SOURCE_DIR}/qcustomplot")

add_subdirectory(${QCUSTOMPLOT_DIR}) # here adding qcustomplot subfolder
add_subdirectory(lib)
add_subdirectory(gui)
add_subdirectory(tests)
add_subdirectory(main)
add_subdirectory(backend)

# the programmer in VS Code is tired of constantly copying one dll file,
# and the command QCUSTOMPLOT_USE_LIBRARY does not work for an unknown reason
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.vscode")
  file(GLOB_RECURSE QCUSTOMPLOTDLLFILES "${CMAKE_BINARY_DIR}/qcustomplot/*.dll")

  foreach(file ${QCUSTOMPLOTDLLFILES})
    file(COPY ${file} DESTINATION ${CMAKE_BINARY_DIR}/main)
  endforeach()
endif()
