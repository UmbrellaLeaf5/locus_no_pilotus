# language: CMake

function(load_qcustomplot_dll START_DIR)
  if(EXISTS "${START_DIR}/.vscode")
    # add needed files to QCUSTOMPLOTDLLFILES
    file(GLOB_RECURSE QCUSTOMPLOTDLLFILES "${CMAKE_BINARY_DIR}/libqcustomplot.dll")

    if(QCUSTOMPLOTDLLFILES)
      message(STATUS "Found ${START_DIR}/.vscode, copying libqcustomplot.dll to build")
    else()
      message(STATUS "warning: libqcustomplot.dll not found in build folder, please build and reconfigure the project")
    endif()

    # copy from QCUSTOMPLOTDLLFILES to dir in binary
    foreach(file ${QCUSTOMPLOTDLLFILES})
      if(QCUSTOMPLOTDLLFILES)
        # copy to main and tests, where qcustomplot is used
        file(COPY ${file} DESTINATION ${CMAKE_BINARY_DIR}/main)
        file(COPY ${file} DESTINATION ${CMAKE_BINARY_DIR}/tests)
      endif()
    endforeach()
    return()
  endif()
endfunction()
