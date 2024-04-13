cmake_minimum_required(VERSION 3.20)

project(tests VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-DTEST_PLOTS")

file(GLOB_RECURSE PROJECT_SOURCES "*.h" "*.cpp" "*.ui")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable(tests
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
  )

# Define target properties for Android with Qt 6 as:
# set_property(TARGET tests APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
# ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
  if(ANDROID)
    add_library(tests SHARED
      ${PROJECT_SOURCES}
    )

  # Define properties for Android with Qt 5 after find_package() calls as:
  # set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
  else()
    add_executable(tests
      ${PROJECT_SOURCES}
    )
  endif()
endif()

target_link_libraries(tests PUBLIC Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport)

target_link_libraries(tests PRIVATE lib)
target_link_libraries(tests PRIVATE backend)

target_link_libraries(tests PRIVATE ${Boost_LIBRARIES})

target_compile_definitions(tests PRIVATE QCUSTOMPLOT_USE_LIBRARY)
target_link_libraries(tests PUBLIC qcustomplot)

set_target_properties(tests PROPERTIES
  MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
  MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
  MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

include(${CMAKESCRIPTS_DIR}/scripts_for_vscode.cmake)
add_qt_runtime(${CMAKE_CURRENT_SOURCE_DIR} tests)

find_package(IcecreamCpp)
include_directories(${IcecreamCpp_INCLUDE_DIRS})

if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(tests)
endif()
