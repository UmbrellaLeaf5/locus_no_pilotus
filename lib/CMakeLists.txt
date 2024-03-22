cmake_minimum_required(VERSION 3.20)

project(lib VERSION 0.1 LANGUAGES CXX)

file(GLOB PROJECT_SOURCES "*.h" "*.cpp")

add_library(lib STATIC ${PROJECT_SOURCES})

install(TARGETS lib
  RUNTIME DESTINATION "${Qt${QT_VERSION_MAJOR}_DIR}"
)
