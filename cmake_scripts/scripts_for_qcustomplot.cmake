# language: CMake

function(replace_include_qcustomplot_in_autogen BUILD_DIR)
  if(EXISTS "${BUILD_DIR}/main/main_autogen/include/ui_mainwindow.h")
    message(STATUS "Found ${BUILD_DIR}/main/main_autogen/include/ui_mainwindow.h , replacing qcustomplot include")

    # open the file where you need to replace the line in FILE_CONTENT
    file(READ "${BUILD_DIR}/main/main_autogen/include/ui_mainwindow.h" FILE_CONTENT)

    # replace the string using REGEX and write it to MODIFIED_CONTENT
    string(REGEX REPLACE "#include \"../qcustomplot/qcustomplot.h\""
      "#include \"../qcustomplot/lib/qcustomplot.h\"" MODIFIED_CONTENT "${FILE_CONTENT}")

    # rewrite the contents of MODIFIED_CONTENT to the file
    file(WRITE "${BUILD_DIR}/main/main_autogen/include/ui_mainwindow.h" "${MODIFIED_CONTENT}")
  else()
    message(STATUS "warning: ${BUILD_DIR}/main/main_autogen/include does not exist, please build and reconfigure the project")
  endif()
endfunction()

function(load_qcustomplot_dll START_DIR)
  if(EXISTS "${START_DIR}/qcustomplot")
    # add needed files to QCUSTOMPLOTDLLFILES
    file(GLOB_RECURSE QCUSTOMPLOTDLLFILES "${CMAKE_BINARY_DIR}/libqcustomplot.dll")

    if(QCUSTOMPLOTDLLFILES)
      message(STATUS "Found libqcustomplot.dll, copying to build")
    else()
      file(GLOB_RECURSE QCUSTOMPLOTDLLFILES "${START_DIR}/libqcustomplot.dll")

      if(QCUSTOMPLOTDLLFILES)
        message(STATUS "Found ${QCUSTOMPLOTDLLFILES} , copying libqcustomplot.dll to build")
      else()
        message(STATUS "warning: libqcustomplot.dll not found in build folder, please build and reconfigure the project")
      endif()
    endif()

    # copy from QCUSTOMPLOTDLLFILES to dir in binary
    foreach(file ${QCUSTOMPLOTDLLFILES})
      if(QCUSTOMPLOTDLLFILES)
        # copy to main, where qcustomplot is used
        file(COPY ${file} DESTINATION ${CMAKE_BINARY_DIR}/main)
      endif()
    endforeach()
    return()
  else()
    message(STATUS "warning: ${START_DIR}/qcustomplot does not exist, please install submodule 'https://github.com/legerch/QCustomPlot-library'")
  endif()
endfunction()
