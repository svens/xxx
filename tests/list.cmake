message(STATUS "Enable unittests")
enable_testing()
include(cmake/catch2.cmake)

add_executable(unittests
  tests/common.hpp
  tests/common.cpp
  tests/error.cpp
)

target_link_libraries(unittests
  ${PROJECT_NAME}
  Catch2::Catch2
  ${${PROJECT_NAME}_DEP_LIBS}
)

add_test(unittests unittests)
