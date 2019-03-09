message(STATUS "Enable benchmarks")
include(cmake/gbench.cmake)

add_executable(bench
  bench/main.cpp
)

target_link_libraries(bench
  ${PROJECT_NAME}
  benchmark
  ${${PROJECT_NAME}_DEP_LIBS}
)

add_dependencies(bench benchmark)
