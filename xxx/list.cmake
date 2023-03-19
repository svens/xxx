configure_file(
	xxx/version.cpp.in
	version.cpp
	@ONLY
)
list(APPEND xxx_sources ${CMAKE_CURRENT_BINARY_DIR}/version.cpp)

list(APPEND xxx_sources
	xxx/__bits/platform_sdk.hpp
	xxx/error.hpp
	xxx/error.cpp
	xxx/version.hpp
)

list(APPEND xxx_test_sources
	xxx/common.test.hpp
	xxx/common.test.cpp
	xxx/error.test.cpp
	xxx/invoke.bench.cpp
)
