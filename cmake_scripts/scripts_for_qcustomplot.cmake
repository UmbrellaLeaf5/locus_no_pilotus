# language: CMake

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
    message(STATUS "warning: ${START_DIR}/qcustomplot does not exist, please install submodule 'https://github.com/UmbrellaLeaf5/qcustomplot'")
  endif()
endfunction()
