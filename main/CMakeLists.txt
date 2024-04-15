# language: CMake

project(main VERSION 0.1 LANGUAGES CXX)

file(GLOB_RECURSE PROJECT_SOURCES "*.h" "*.cpp" "*.ui"
  "${GUI_DIR}/*.h" "${GUI_DIR}/*.cpp" "${DATATOOLS_DIR}/*.h" "${DATATOOLS_DIR}/*.cpp")

include_directories(${PROJECT_DIR})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable(main
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
  )

# Define target properties for Android with Qt 6 as:
# set_property(TARGET main APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
# ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
  if(ANDROID)
    add_library(main SHARED
      ${PROJECT_SOURCES}
    )

  # Define properties for Android with Qt 5 after find_package() calls as:
  # set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
  else()
    add_executable(main
      ${PROJECT_SOURCES}
    )
  endif()
endif()

target_link_libraries(main PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core)

target_link_libraries(main PRIVATE lib)

target_compile_definitions(main PRIVATE QCUSTOMPLOT_USE_LIBRARY)
target_link_libraries(main PUBLIC qcustomplot)

set_target_properties(main PROPERTIES
  MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
  MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
  MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

include(${CMAKESCRIPTS_DIR}/scripts_for_vscode.cmake)
add_qt_runtime(${CMAKE_CURRENT_SOURCE_DIR} main)

find_package(IcecreamCpp)
include_directories(${IcecreamCpp_INCLUDE_DIRS})

if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(main)
endif()
