function(load_qcustomplot_dll START_DIR)
  if(EXISTS "${START_DIR}/.vscode")
    file(GLOB_RECURSE QCUSTOMPLOTDLLFILES "${CMAKE_BINARY_DIR}/qcustomplot/*.dll")

    foreach(file ${QCUSTOMPLOTDLLFILES})
      file(COPY ${file} DESTINATION ${CMAKE_BINARY_DIR}/main)
    endforeach()
    return()
  endif()

  file(GLOB SUBFOLDERS LIST_DIRECTORIES true ${START_DIR}/*)

  foreach(SUBFOLDER ${SUBFOLDERS})
    if(IS_DIRECTORY ${SUBFOLDER})
      load_qcustomplot_dll(${SUBFOLDER})
    endif()
  endforeach()
endfunction()

function(add_qt_runtime START_DIR TARGET)
  if(EXISTS "${START_DIR}/.vscode")
    install(TARGETS TARGET
      RUNTIME DESTINATION "${Qt${QT_VERSION_MAJOR}_DIR}"
    )
  endif()

  file(GLOB SUBFOLDERS LIST_DIRECTORIES true ${START_DIR}/*)

  foreach(SUBFOLDER ${SUBFOLDERS})
    if(IS_DIRECTORY ${SUBFOLDER})
      add_qt_runtime(${SUBFOLDER} TARGET)
    endif()
  endforeach()
endfunction()
