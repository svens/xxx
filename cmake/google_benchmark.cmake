if(NOT EXISTS extern/google_benchmark/CMakeLists.txt)
  find_package(Git)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} submodule update --init extern/google_benchmark
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
endif()

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable benchmark library testing")
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "Disable benchmark library installing")
add_subdirectory(extern/google_benchmark)
