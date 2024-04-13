function(replace_include_qcustomplot_in_autogen BUILD_DIR)
  if(EXISTS "${BUILD_DIR}/main/main_autogen/include")
    message(STATUS "Found ${BUILD_DIR}/main/main_autogen/include/ui_mainwindow.h, replacing qcustomplot include")

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
