#pragma once // -*- C++ -*-

#if __xxx_os_windows
	// included from header: assume nothing, leak nothing
	#if !defined(WIN32_LEAN_AND_MEAN)
		#define xxx_WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif
	#include <windows.h>
	#if defined(xxx_WIN32_LEAN_AND_MEAN)
		#undef xxx_WIN32_LEAN_AND_MEAN
		#undef WIN32_LEAN_AND_MEAN
	#endif
#else
	// included from source, must be first
	#if defined(_WIN32) || defined(_WIN64)
		#define WIN32_LEAN_AND_MEAN
		#define WIN32_NO_STATUS
		#include <windows.h>
		#undef WIN32_NO_STATUS
		#include <winternl.h>
		#include <ntstatus.h>
	#endif
#endif
