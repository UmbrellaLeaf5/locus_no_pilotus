function(add_icecream_cpp_lib START_DIR)
  # только есть существует папка над проектом с названием "icecream-cpp",
  # мы добавляем библиотеку в CMake
  if(EXISTS "${START_DIR}/../icecream-cpp")
    list(APPEND CMAKE_PREFIX_PATH "${START_DIR}/../icecream-cpp")
    find_package(IcecreamCpp)
    include_directories(SYSTEM ${IcecreamCpp_INCLUDE_DIRS})
    return()
  endif()

  # а также рекурсивно проходимся по надпапкам в поисках .vscode
  file(GLOB ABOVEFOLDERS LIST_DIRECTORIES true "${START_DIR}/../*")

  foreach(ABOVEFOLDER ${ABOVEFOLDERS})
    if(IS_DIRECTORY ${ABOVEFOLDER})
      # если встречаем название проекта, то выходим из рекусрсии
      # (выше уже точно не будет того, что нам нужно)
      if(${ABOVEFOLDER} MATCHES "locus_no_pilotus")
        message("IcecreamCpp not found.")
        return()
      else()
        add_icecream_cpp_lib(${ABOVEFOLDER})
      endif()
    endif()
  endforeach()
endfunction()
