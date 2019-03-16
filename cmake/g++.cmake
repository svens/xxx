set(max_warning_flags -Werror -Wall -Wextra -Weffc++ -pedantic)

add_compile_options(-pipe)
if("${CMAKE_GENERATOR}" STREQUAL "Ninja")
  # Ninja redirects build output and prints it only on error
  # Redirection strips colorization, so let's force it here
  add_compile_options(-fdiagnostics-color)
endif()

if(Coverage)
  message(STATUS "Unittests coverage build")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -coverage")

  find_program(LCOV lcov)
  if(NOT LCOV)
    message(FATAL_ERROR "Executable lcov not found")
  endif()
  set(LCOV_ARGS
    --quiet
    --base-directory ${CMAKE_SOURCE_DIR}
    --directory .
    --rc lcov_branch_coverage=1
  )

  if(DEFINED ENV{COV})
    set(COV_TOOL $ENV{COV})
  else()
    set(COV_TOOL gcov)
  endif()
  find_program(COV ${COV_TOOL})
  if (NOT COV)
    message(FATAL_ERROR "Executable $ENV{COV} not found")
  endif()
  set(LCOV_ARGS ${LCOV_ARGS} --gcov-tool ${COV})

  find_program(GENHTML genhtml)
  if(NOT GENHTML)
    message(FATAL_ERROR "Executable genhtml not found")
  endif()

  add_custom_target(${CMAKE_PROJECT_NAME}-cov
    DEPENDS unittests
    COMMENT "Generate coverage information"

    # Initialize coverage generation
    COMMAND ${LCOV} ${LCOV_ARGS} --zerocounters
    COMMAND ${LCOV} ${LCOV_ARGS} --initial --capture --no-external --derive-func-data --output-file ${CMAKE_PROJECT_NAME}-base.info

    # Run and extract
    COMMAND ${CMAKE_COMMAND} --build . --target test
    COMMAND ${LCOV} ${LCOV_ARGS} --capture --no-external --derive-func-data --output-file ${CMAKE_PROJECT_NAME}-tests.info
    COMMAND ${LCOV} ${LCOV_ARGS} --add-tracefile ${CMAKE_PROJECT_NAME}-base.info --add-tracefile ${CMAKE_PROJECT_NAME}-tests.info --output-file ${CMAKE_PROJECT_NAME}.info
    COMMAND ${LCOV} ${LCOV_ARGS} --remove ${CMAKE_PROJECT_NAME}.info '*.test.?pp' '${PROJECT_SOURCE_DIR}/extern/*' --output-file ${CMAKE_PROJECT_NAME}.info
    COMMAND ${LCOV} ${LCOV_ARGS} --list ${CMAKE_PROJECT_NAME}.info
    COMMAND ${LCOV} ${LCOV_ARGS} --summary ${CMAKE_PROJECT_NAME}.info
  )

  add_custom_command(TARGET ${CMAKE_PROJECT_NAME}-cov POST_BUILD
    COMMENT "Open ${CMAKE_BINARY_DIR}/cov/index.html in your browser"
    COMMAND ${GENHTML} --rc lcov_branch_coverage=1 -q --demangle-cpp --legend --output-directory cov ${CMAKE_PROJECT_NAME}.info
  )
endif()
