function(load_qcustomplot_dll START_DIR)
  if(EXISTS "${START_DIR}/.vscode")
    file(GLOB_RECURSE QCUSTOMPLOTDLLFILES "${CMAKE_BINARY_DIR}/libqcustomplot.dll")

    if(QCUSTOMPLOTDLLFILES)
      message(STATUS "Found ${START_DIR}/.vscode, copying libqcustomplot.dll to build")
    else()
      message(STATUS "warning: libqcustomplot.dll not found in build folder, please build and reconfigure the project")
    endif()

    foreach(file ${QCUSTOMPLOTDLLFILES})
      if(QCUSTOMPLOTDLLFILES)
        file(COPY ${file} DESTINATION ${CMAKE_BINARY_DIR}/main)
      endif()
    endforeach()
    return()
  endif()
endfunction()

function(add_qt_runtime START_DIR TARGET)
  if(EXISTS "${START_DIR}/.vscode")
    message(STATUS "Found ${START_DIR}/.vscode, installing RUNTIME DESTINATION Qt")
    install(TARGETS TARGET
      RUNTIME DESTINATION "${Qt${QT_VERSION_MAJOR}_DIR}"
    )
  endif()
endfunction()
