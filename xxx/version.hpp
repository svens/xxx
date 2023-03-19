#pragma once // -*- C++ -*-

#include <cstddef>
#include <cstdint>

#if __has_include(<version>)
	#include <version>
#endif

// project namespace
#define __xxx_begin namespace xxx { inline namespace v0 {
#define __xxx_end   }} // namespace xxx::v0

__xxx_begin

//
// project version
//

extern const char version[];
extern const int version_major, version_minor, version_patch;

//
// build type
//

#define __xxx_build_debug 0
#define __xxx_build_release 0

#if NDEBUG && !defined(_DEBUG)
	#undef __xxx_build_release
	#define __xxx_build_release 1
#else
	#undef __xxx_build_debug
	#define __xxx_build_debug 1
#endif

enum class build_type
{
	debug,
	release,
};

constexpr build_type build =
#if __xxx_build_debug
	build_type::debug
#elif __xxx_build_release
	build_type::release
#endif
;

//
// compiler
//

#define __xxx_compiler_clang 0
#define __xxx_compiler_gnu 0
#define __xxx_compiler_msvc 0

#if defined(__clang__)
	#undef __xxx_compiler_clang
	#define __xxx_compiler_clang 1
#elif defined(__GNUC__)
	#undef __xxx_compiler_gnu
	#define __xxx_compiler_gnu 1
#elif defined(_MSC_BUILD)
	#undef __xxx_compiler_msvc
	#define __xxx_compiler_msvc 1
#else
	#error "Unsupported compiler"
#endif

enum class compiler_type
{
	clang,
	gnu,
	msvc,
};

constexpr compiler_type compiler =
#if __xxx_compiler_clang
	compiler_type::clang
#elif __xxx_compiler_gnu
	compiler_type::gnu
#elif __xxx_compiler_msvc
	compiler_type::msvc
#endif
;

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
#else
	#error "Unsupported OS"
#endif

enum class os_type
{
	linux,
	macos,
	windows,
};

constexpr os_type os =
#if __xxx_os_linux
	os_type::linux
#elif __xxx_os_macos
	os_type::macos
#elif __xxx_os_windows
	os_type::windows
#endif
;

__xxx_end
