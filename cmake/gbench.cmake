if(NOT EXISTS tps/gbench/CMakeLists.txt)
  find_package(Git)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} submodule update --init tps/gbench
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
endif()

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable benchmark library testing")
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "Disable benchmark library installing")
add_subdirectory(tps/gbench)

if(CMAKE_COMPILER_IS_GNUCXX OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
  target_compile_options(benchmark PUBLIC -Wno-effc++)
elseif(MSVC)
  target_compile_options(benchmark PUBLIC /wd4244)
endif()
