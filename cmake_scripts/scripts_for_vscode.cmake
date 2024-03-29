function(load_qcustomplot_dll START_DIR)
  # только есть существует папка над проектом с названием ".vscode",
  # мы добавляем qcustomplot dll в папку с main
  if(EXISTS "${START_DIR}/.vscode")
    file(GLOB_RECURSE QCUSTOMPLOTDLLFILES "${CMAKE_BINARY_DIR}/qcustomplot/*.dll")

    foreach(file ${QCUSTOMPLOTDLLFILES})
      file(COPY ${file} DESTINATION ${CMAKE_BINARY_DIR}/main)
    endforeach()
    return()
  endif()

  # а также рекурсивно проходимся по подпапкам в поисках .vscode
  file(GLOB SUBFOLDERS LIST_DIRECTORIES true ${START_DIR}/*)

  foreach(SUBFOLDER ${SUBFOLDERS})
    if(IS_DIRECTORY ${SUBFOLDER})
      load_qcustomplot_dll(${SUBFOLDER})
    endif()
  endforeach()
endfunction()

function(add_qt_runtime START_DIR TARGET)
  # только есть существует папка над проектом с названием ".vscode",
  # мы добавляем пути для компиляции к папкам Qt
  if(EXISTS "${START_DIR}/.vscode")
    install(TARGETS TARGET
      RUNTIME DESTINATION "${Qt${QT_VERSION_MAJOR}_DIR}"
    )
  endif()

  # а также рекурсивно проходимся по подпапкам в поисках .vscode
  file(GLOB SUBFOLDERS LIST_DIRECTORIES true ${START_DIR}/*)

  foreach(SUBFOLDER ${SUBFOLDERS})
    if(IS_DIRECTORY ${SUBFOLDER})
      add_qt_runtime(${SUBFOLDER} TARGET)
    endif()
  endforeach()
endfunction()
