cmake_minimum_required(VERSION 3.20)

project(AdjacencyMatrix VERSION 0.1 LANGUAGES CXX)

file(GLOB PROJECT_SOURCES "*.h" "*.cpp")

add_library(AdjacencyMatrix STATIC ${PROJECT_SOURCES})

