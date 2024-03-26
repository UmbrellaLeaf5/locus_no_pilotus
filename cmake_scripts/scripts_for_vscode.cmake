function(load_qcustomplot_dll START_DIR)
  if(EXISTS "${START_DIR}/.vscode")
    file(GLOB_RECURSE QCUSTOMPLOTDLLFILES "${CMAKE_BINARY_DIR}/qcustomplot/*.dll")

    foreach(file ${QCUSTOMPLOTDLLFILES})
      file(COPY ${file} DESTINATION ${CMAKE_BINARY_DIR}/main)
    endforeach()
    return()
  endif()

  file(GLOB SUBFOLDERS LIST_DIRECTORIES true ${
  START_DIR}/*)

  foreach(SUBFOLDER ${SUBFOLDERS})
    if(IS_DIRECTORY ${SUBFOLDER})
      load_qcustomplot_dll(${SUBFOLDER})
    endif()
  endforeach()
endfunction()
