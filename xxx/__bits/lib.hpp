#pragma once // -*- C++ -*-

#include <cstddef>
#include <cstdint>

// project namespace
#define __xxx_begin namespace xxx { inline namespace v0 {
#define __xxx_end   }} // namespace xxx::v0

__xxx_begin

//
// build OS
//

#define __xxx_os_linux 0
#define __xxx_os_macos 0
#define __xxx_os_windows 0

#if defined(__linux__)
	#undef __xxx_os_linux
	#define __xxx_os_linux 1
#elif defined(__APPLE__)
	#undef __xxx_os_macos
	#define __xxx_os_macos 1
#elif defined(_WIN32) || defined(_WIN64)
	#undef __xxx_os_windows
	#define __xxx_os_windows 1
#endif

constexpr bool is_linux_build = __xxx_os_linux == 1;
constexpr bool is_macos_build = __xxx_os_macos == 1;
constexpr bool is_windows_build = __xxx_os_windows == 1;

//
// build configuration
//

constexpr bool is_release_build =
#if NDEBUG
	true
#else
	false
#endif
;

__xxx_end
