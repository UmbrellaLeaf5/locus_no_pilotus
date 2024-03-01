cmake_minimum_required(VERSION 3.20)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS PrintSupport)

set(Boost_USE_STATIC_LIBS OFF)

find_package(Boost REQUIRED COMPONENTS locale unit_test_framework)

add_subdirectory(lib)
# add_subdirectory(tests)
add_subdirectory(main)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/qcustomplot) # here adding qcustomplot subfolder
#add_subdirectory(qcustomplot)


