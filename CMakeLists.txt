# language: CMake

# ---------------------------------     Project setup      ---------------------------------
cmake_minimum_required(VERSION 3.20)

project(locus_no_pilotus LANGUAGES CXX)

# ---------------------------------    Set C++ settings    ---------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++17 -O2")

# less speed, more warnings = less potential errors in code
# flags using source: https://codeforces.com/blog/entry/15547?locale=ru
# (commented because of qcustomplot warnings)
# set(CMAKE_CXX_FLAGS " -Wall -Wextra -pedantic -std=c++17 -O2 -Wfloat-equal -Wconversion -Wlogical-op -Wduplicated-cond")

# ---------------------------------   Set CMake settings   ---------------------------------
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# include file with extra project paths
include(cmake_paths.cmake)

# ---------------------------------         Find Qt        ---------------------------------
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core PrintSupport REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core PrintSupport REQUIRED)

# ---------------------------------       Find Boost       ---------------------------------
set(Boost_USE_STATIC_LIBS OFF)

find_package(Boost REQUIRED COMPONENTS locale unit_test_framework)

# ---------------------------------   Submodules folders   ---------------------------------
# ---------------------------------      (and sripts)      ---------------------------------

# because of icecream-cpp CMake settings we need to move one file to bin dir
include(${CMAKESCRIPTS_DIR}/scripts_for_icecream_cpp.cmake)
move_icecream_hpp_to_build_dir(${CMAKE_CURRENT_SOURCE_DIR})

# and add it to CMAKE_PREFIX_PATH manually
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/icecream-cpp")
add_subdirectory(${ICECREAM-CPP_DIR}) # here adding icecream-cpp subfolder
find_package(IcecreamCpp) # here finding icecream-cpp

# the command QCUSTOMPLOT_USE_LIBRARY does not work for an unknown reason
include(${CMAKESCRIPTS_DIR}/scripts_for_qcustomplot.cmake)
load_qcustomplot_dll(${CMAKE_CURRENT_SOURCE_DIR}) # copy one dll file
add_subdirectory(${QCUSTOMPLOT_DIR}) # here adding qcustomplot subfolder

# ---------------------------------    Our code subdirs    ---------------------------------
add_subdirectory(lib)
add_subdirectory(tests)
add_subdirectory(main)

# ------------------------------------------------------------------------------------------

# copy images to build directory
file(COPY ${IMAGES_DIR} DESTINATION ${CMAKE_BINARY_DIR})
