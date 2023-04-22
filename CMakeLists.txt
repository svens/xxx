cmake_minimum_required(VERSION 3.12)

project(xxx LANGUAGES CXX)
include(cmake/project_version.cmake)
message(STATUS "${PROJECT_NAME} ${PROJECT_VERSION}")

option(xxx_test "Build tests" ON)
option(xxx_doc "Generate documentation" OFF)
option(xxx_samples "Build samples" OFF)

if("${CMAKE_BUILD_TYPE};${CMAKE_CONFIGURATION_TYPES}" MATCHES ".*Coverage.*")
	set(xxx_test ON)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/cxx.cmake)

include(xxx/list.cmake)
cxx_library(xxx
	ALIAS xxx::xxx
	SOURCES ${xxx_sources}
)

if(xxx_test)
	cxx_test(xxx_test
		SOURCES ${xxx_test_sources}
		LIBRARIES xxx::xxx
		COVERAGE_BASE_DIR ${CMAKE_SOURCE_DIR}/xxx
	)
endif()

if(xxx_doc)
	cxx_doc(xxx
		MAIN_PAGE ${CMAKE_SOURCE_DIR}/README.md
		DIRECTORY ${CMAKE_SOURCE_DIR}/xxx
	)
endif()

if(xxx_samples)
	include(sample/list.cmake)
	cxx_executable(xxx_sample
		SOURCES ${xxx_sample_sources}
		LIBRARIES xxx::xxx
	)
endif()
