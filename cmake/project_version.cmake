find_package(Git)
if(GIT_FOUND)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} describe --match "v[0-9]*.[0-9]*.[0-9]*" --always --tags --dirty
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE CMAKE_PROJECT_VERSION
    ERROR_QUIET
  )
endif()

if(CMAKE_PROJECT_VERSION)
  # v{VERSION}-{N}-g{HASH} -> {VERSION}-{HASH}
  string(STRIP ${CMAKE_PROJECT_VERSION} CMAKE_PROJECT_VERSION)
  string(REGEX
    REPLACE "^v?([0-9]*.[0-9]*.[0-9]*)-[0-9]+-g([0-9a-f]*)" "\\1-\\2"
    CMAKE_PROJECT_VERSION
    ${CMAKE_PROJECT_VERSION}
  )
  string(REGEX
    REPLACE "^v(.*)" "\\1"
    CMAKE_PROJECT_VERSION
    ${CMAKE_PROJECT_VERSION}
  )
else()
  set(CMAKE_PROJECT_VERSION "0.0.0")
endif()
