cmake_minimum_required(VERSION 3.2)

project(xxx)
include(cmake/project_version.cmake)
message(STATUS "${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_VERSION}")


# User settings {{{1

option(xxx_unittests "Build unittests" ON)
option(xxx_benchmarks "Build benchmarking application" OFF)
option(xxx_docs "Generate documentation" OFF)

if(CMAKE_BUILD_TYPE MATCHES Coverage)
  set(CMAKE_BUILD_TYPE "Debug")
  set(Coverage ON)
  set(xxx_unittests ON)
  set(xxx_benchmarks OFF)
endif()


# Build settings {{{1

include(GNUInstallDirs)

# compiler
if(CMAKE_COMPILER_IS_GNUCXX)
  include(cmake/g++.cmake)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  include(cmake/clang++.cmake)
elseif(MSVC)
  include(cmake/msvc.cmake)
else()
  message(WARNING "Unknown compiler")
endif()

# host
if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
  include(cmake/macos.cmake)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  include(cmake/linux.cmake)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  include(cmake/windows.cmake)
else()
  message(WARNING "Unknown system")
endif()


# Targets {{{1

include(xxx/list.cmake)

add_library(xxx
  ${xxx_api_sources}
  ${xxx_impl_sources}
)
add_library(xxx::xxx ALIAS xxx)
target_include_directories(xxx
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_compile_features(xxx PUBLIC cxx_std_17)
target_compile_options(xxx PRIVATE ${max_warning_flags})
set_target_properties(xxx PROPERTIES CXX_EXTENSIONS OFF)

include(cmake/tidy.cmake)
tidy(xxx)
include(cmake/iwyu.cmake)
iwyu(xxx)


# Tests
if(xxx_unittests)
  message(STATUS "Enable unittests")
  enable_testing()
  include(cmake/catch2.cmake)
  add_executable(unittests ${xxx_unittests_sources})
  target_compile_options(unittests PRIVATE ${max_warning_flags})
  target_link_libraries(unittests xxx::xxx Catch2::Catch2)
  include(extern/catchorg_catch2/contrib/Catch.cmake)
  catch_discover_tests(unittests)
endif()


# Benchmarks
if(xxx_benchmarks)
  message(STATUS "Enable benchmarks")
  include(cmake/google_benchmark.cmake)
  include(bench/list.cmake)
  add_executable(benchmarks ${xxx_benchmarks_sources})
  target_link_libraries(benchmarks xxx::xxx benchmark)
endif()


# Documentation
if(xxx_docs)
  find_package(Doxygen)
  if(DOXYGEN_FOUND)
    message(STATUS "Enable documentation")
    configure_file(
      ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Doxyfile.in
      ${CMAKE_BINARY_DIR}/Doxyfile
    )
    add_custom_target(${CMAKE_PROJECT_NAME}-doc
      ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
      COMMENT "Generating documentation"
    )
  else()
    message(STATUS "Disable documentation")
  endif()
endif()


# Packaging {{{1

set(CPACK_PACKAGE_VERSION "${CMAKE_PROJECT_VERSION}")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
list(APPEND CPACK_GENERATOR "TGZ")
list(APPEND CPACK_SOURCE_GENERATOR "TGZ")

# headers
foreach(file ${xxx_api_sources})
  get_filename_component(path ${file} PATH)
  install(FILES ${file}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${path}
    COMPONENT dev
  )
endforeach()
list(APPEND CPACK_COMPONENTS_ALL dev)

# library
install(TARGETS xxx
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  COMPONENT lib
)
list(APPEND CPACK_COMPONENTS_ALL lib)

include(CPack)
