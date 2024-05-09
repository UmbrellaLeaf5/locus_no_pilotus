# language: CMake

function(move_icecream_hpp_to_build_dir START_DIR)
  if(EXISTS "${START_DIR}/icecream-cpp")
    message(STATUS "Found " ${START_DIR}/icecream-cpp", copying icecream.hpp to build")

    # add needed files to ICLUDEHEADERFILES
    file(GLOB ICLUDEHEADERFILES "${START_DIR}/icecream-cpp/*.hpp" "${START_DIR}/icecream-cpp/*.h")

    # copy from ICLUDEHEADERFILES to include dir in binary
    foreach(file ${ICLUDEHEADERFILES})
      file(COPY ${file} DESTINATION "${CMAKE_BINARY_DIR}/include")
    endforeach()
    return()
  else()
    message(FATAL_ERROR "${START_DIR}/icecream-cpp does not exist, please install submodule 'https://github.com/renatoGarcia/icecream-cpp'")
  endif()
endfunction()