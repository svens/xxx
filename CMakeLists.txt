cmake_minimum_required(VERSION 3.2)

project(xxx)
include(cmake/project_version.cmake)
message(STATUS "${PROJECT_NAME} ${PROJECT_VERSION}")


# User settings {{{1

option(${PROJECT_NAME}_unittests "Build unittests" ON)
option(${PROJECT_NAME}_bench "Build benchmarking application" OFF)
option(${PROJECT_NAME}_docs "Generate documentation" OFF)

if(CMAKE_BUILD_TYPE MATCHES Coverage)
  set(CMAKE_BUILD_TYPE "Debug")
  set(COVERAGE ON)
  set(${PROJECT_NAME}_unittests ON)
  set(${PROJECT_NAME}_bench OFF)
endif()


# Build settings {{{1

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
)

if(CMAKE_COMPILER_IS_GNUCXX)
  include(cmake/g++.cmake)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  include(cmake/clang++.cmake)
elseif(MSVC)
  include(cmake/msvc.cmake)
else()
  message(WARNING "Unknown compiler")
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
  include(cmake/macos.cmake)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  include(cmake/linux.cmake)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  include(cmake/windows.cmake)
else()
  message(WARNING "Unknown system")
endif()

message(STATUS "Generate ${PROJECT_NAME}/config.hpp")
configure_file(
  ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/config.hpp.in
  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/config.hpp
)
set_source_files_properties(${CMAKE_BINARY_DIR}/${PROJECT_NAME}/config.hpp
  PROPERTIES GENERATED TRUE
)

# Targets {{{1

include(${PROJECT_NAME}/list.cmake)
if(${PROJECT_NAME}_unittests)
  include(tests/list.cmake)
endif()
if(${PROJECT_NAME}_bench)
  include(bench/list.cmake)
endif()
