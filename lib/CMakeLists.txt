# language: CMake

project(lib VERSION 0.1 LANGUAGES CXX)

file(GLOB_RECURSE PROJECT_SOURCES "*.h" "*.cpp"
  "${MATH_DIR}/*.h" "${MATH_DIR}/*.cpp")

include_directories(${PROJECT_DIR})

add_library(lib STATIC ${PROJECT_SOURCES})

target_link_libraries(lib PRIVATE Qt${QT_VERSION_MAJOR}::Core)

find_package(IcecreamCpp)
include_directories(${IcecreamCpp_INCLUDE_DIRS})
