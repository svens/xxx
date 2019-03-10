list(APPEND ${PROJECT_NAME}_sources
  xxx/__bits/platform_sdk.hpp
  xxx/error.hpp
  xxx/error.cpp
)

list(APPEND ${PROJECT_NAME}_unittests_sources
  xxx/common.test.hpp
  xxx/common.test.cpp
  xxx/error.test.cpp
)

add_library(${PROJECT_NAME}
  ${${PROJECT_NAME}_sources}
  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/config.hpp
)
include(cmake/clang_tidy.cmake)
include(cmake/iwyu.cmake)

if(${PROJECT_NAME}_unittests)
  message(STATUS "Enable unittests")
  enable_testing()
  include(cmake/catch2.cmake)

  add_executable(unittests ${${PROJECT_NAME}_unittests_sources})

  target_link_libraries(unittests
    ${PROJECT_NAME}
    Catch2::Catch2
    ${${PROJECT_NAME}_DEP_LIBS}
  )

  add_test(unittests unittests)
endif()
