if(NOT EXISTS extern/catchorg_catch2/CMakeLists.txt)
  find_package(Git)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} submodule update --init extern/catchorg_catch2
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
endif()

add_subdirectory(extern/catchorg_catch2)
