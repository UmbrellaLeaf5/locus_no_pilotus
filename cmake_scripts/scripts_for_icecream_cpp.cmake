function(add_icecream_cpp_lib START_DIR)
  set(MAX_RECURSION_DEPTH 100)

  if(EXISTS "${START_DIR}/../icecream-cpp")
    list(APPEND CMAKE_PREFIX_PATH "${START_DIR}/../icecream-cpp")
    find_package(IcecreamCpp)
    include_directories(SYSTEM ${IcecreamCpp_INCLUDE_DIRS})
    return()
  endif()

  file(GLOB ABOVEFOLDERS LIST_DIRECTORIES true "${START_DIR}/../*")

  foreach(ABOVEFOLDER ${ABOVEFOLDERS})
    if(IS_DIRECTORY ${ABOVEFOLDER})
      add_icecream_cpp_lib(${ABOVEFOLDER})
    endif()
  endforeach()

  if(${__recursion_depth} EQUAL ${MAX_RECURSION_DEPTH})
    message("IceCreamCpp not found")
  endif()
endfunction()
