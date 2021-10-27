cmake_minimum_required(VERSION 3.12)

project(xxx LANGUAGES CXX)
include(cmake/project_version.cmake)
message(STATUS "${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_VERSION}")

option(xxx_test "Build tests" ON)
option(xxx_bench "Build benchmarks" OFF)
option(xxx_doc "Generate documentation" OFF)
option(xxx_samples "Build samples" OFF)

if(CMAKE_BUILD_TYPE MATCHES "Coverage")
	set(CMAKE_BUILD_TYPE "Debug")
	set(Coverage ON)
	set(xxx_test ON)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/cxx.cmake)

include(xxx/list.cmake)
cxx_library(xxx
	SOURCES ${xxx_sources}
)

set(xxx_libraries xxx::xxx)

if(xxx_test)
	cxx_test(xxx_test
		SOURCES ${xxx_test_sources}
		LIBRARIES ${xxx_libraries}
		COVERAGE ${Coverage}
		COVERAGE_BASE_DIR ${CMAKE_SOURCE_DIR}/xxx
	)
endif()

if(xxx_bench)
	include(bench/list.cmake)
	cxx_benchmark(xxx_bench
		SOURCES ${xxx_bench_sources}
		LIBRARIES ${xxx_libraries}
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
		LIBRARIES ${xxx_libraries}
	)
endif()
