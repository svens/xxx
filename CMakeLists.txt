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

if(${PROJECT_NAME}_bench)
  include(bench/list.cmake)
endif()

if(${PROJECT_NAME}_docs)
  include(cmake/doxygen.cmake)
endif()


# Packaging {{{1

set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${PROJECT_SOURCE_DIR}/README.md")
list(APPEND CPACK_GENERATOR "TGZ")

# library
install(TARGETS ${PROJECT_NAME}
  ARCHIVE
  DESTINATION lib
  COMPONENT libraries
)
list(APPEND CPACK_COMPONENTS_ALL libraries)

# headers
get_target_property(sources ${PROJECT_NAME} SOURCES)
foreach(source ${sources})
  get_filename_component(source_ext ${source} EXT)
  if(${source_ext} STREQUAL ".hpp")
    get_filename_component(source_path ${source} PATH)
    string(REPLACE "${CMAKE_BINARY_DIR}/" "" source_path ${source_path})
    install(FILES ${source}
      DESTINATION include/${source_path}
      COMPONENT headers
    )
  endif()
endforeach()
list(APPEND CPACK_COMPONENT_ALL headers)
set(CPACK_COMPONENT_HEADERS_DEPENDS libraries)

include(CPack)
