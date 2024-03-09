cmake_minimum_required(VERSION 3.20)

project(backend VERSION 0.1 LANGUAGES CXX)

file(GLOB PROJECT_SOURCES "*.h" "*.cpp")

add_library(backend STATIC ${PROJECT_SOURCES})
