#
# GNU G++ options
#

set(CMAKE_CXX_FLAGS "-Werror -Wall -Wextra -Weffc++ -pedantic -pipe")
set(CMAKE_CXX_FLAGS_DEBUG "-D_DEBUG -ggdb -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3")

if("${CMAKE_GENERATOR}" STREQUAL "Ninja")
  # Ninja redirects build output and prints it only on error
  # Redirection strips colorization, so let's force it here
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color")
endif()


#
# Test coverage related stuff
#

if(COVERAGE)
  message(STATUS "Unittests coverage build")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -coverage")

  find_program(LCOV lcov)
  if(NOT LCOV)
    message(FATAL_ERROR "Executable lcov not found")
  endif()
  set(LCOV_ARGS
    --quiet
    --base-directory ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}
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

  add_custom_target(${PROJECT_NAME}-cov
    DEPENDS unittests
    COMMENT "Generate coverage information"

    # Initialize coverage generation
    COMMAND ${LCOV} ${LCOV_ARGS} --zerocounters
    COMMAND ${LCOV} ${LCOV_ARGS} --initial --capture --no-external --derive-func-data --output-file ${PROJECT_NAME}-base.info

    # Run and extract
    COMMAND ${CMAKE_COMMAND} --build . --target test
    COMMAND ${LCOV} ${LCOV_ARGS} --capture --no-external --derive-func-data --output-file ${PROJECT_NAME}-tests.info
    COMMAND ${LCOV} ${LCOV_ARGS} --add-tracefile ${PROJECT_NAME}-base.info --add-tracefile ${PROJECT_NAME}-tests.info --output-file ${PROJECT_NAME}.info
    COMMAND ${LCOV} ${LCOV_ARGS} --remove ${PROJECT_NAME}.info '*.test.?pp' '${PROJECT_SOURCE_DIR}/tps/*' --output-file ${PROJECT_NAME}.info
    COMMAND ${LCOV} ${LCOV_ARGS} --list ${PROJECT_NAME}.info
    COMMAND ${LCOV} ${LCOV_ARGS} --summary ${PROJECT_NAME}.info
  )

  add_custom_command(TARGET ${PROJECT_NAME}-cov POST_BUILD
    COMMENT "Open ${CMAKE_BINARY_DIR}/cov/index.html in your browser"
    COMMAND ${GENHTML} --rc lcov_branch_coverage=1 -q --demangle-cpp --legend --output-directory cov ${PROJECT_NAME}.info
  )
endif()
