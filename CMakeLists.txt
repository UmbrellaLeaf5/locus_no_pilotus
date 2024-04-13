# ----------------------     Project setup      ----------------------
cmake_minimum_required(VERSION 3.20)

project(locus_no_pilotus)

# ----------------------   Set CMake settings   ----------------------
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include file with extra project paths
include(cmake_paths.cmake)

# ----------------------         Find Qt        ----------------------
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core PrintSupport REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core PrintSupport REQUIRED)

# ----------------------       Find Boost       ----------------------
set(Boost_USE_STATIC_LIBS OFF)

find_package(Boost REQUIRED COMPONENTS locale unit_test_framework)

# ----------------------   Submodules folders   ----------------------
# ----------------------      (and sripts)      ----------------------

# because of icecream-cpp CMake settings we need to move one file to bin dir
include(${CMAKESCRIPTS_DIR}/scripts_for_icecream_cpp.cmake)
move_icecream_hpp_to_build_dir(${CMAKE_CURRENT_SOURCE_DIR})

# and add it to CMAKE_PREFIX_PATH manually
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/icecream-cpp")
add_subdirectory(${ICECREAM-CPP_DIR}) # here adding icecream-cpp subfolder

# because of qcustomplot [module] CMake settings we need to change include in ui_mainwindow.h
include(${CMAKESCRIPTS_DIR}/scripts_for_qcustomplot.cmake)
replace_include_qcustomplot_in_autogen(${CMAKE_BINARY_DIR})
add_subdirectory(${QCUSTOMPLOT_DIR}) # here adding qcustomplot subfolder

# ----------------------    Our code folders    ----------------------
add_subdirectory(lib)
add_subdirectory(gui)
add_subdirectory(tests)
add_subdirectory(main)
add_subdirectory(backend)

# --------------------------------------------------------------------

# the programmer in VS Code is tired of constantly copying one dll file,
# and the command QCUSTOMPLOT_USE_LIBRARY does not work for an unknown reason
include(${CMAKESCRIPTS_DIR}/scripts_for_vscode.cmake)
load_qcustomplot_dll(${CMAKE_CURRENT_SOURCE_DIR})

# add images to build directory
file(COPY ${IMAGES_DIR} DESTINATION ${CMAKE_BINARY_DIR})
