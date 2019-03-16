#pragma once


// project namespace
#define __xxx_begin namespace xxx { inline namespace v0 {
#define __xxx_end   }} // namespace xxx::v0


// arch
#if defined(__i386__) || defined(_M_IX86)
  #define __xxx_arch_x86 1
#elif defined(__x86_64__) || defined(_M_X64)
  #define __xxx_arch_x64 1
#endif


// os
#if defined(__linux__)
  #define __xxx_os_linux 1
#elif defined(__APPLE__)
  #define __xxx_os_macos 1
#elif defined(_WIN32) || defined(_WIN64)
  #define __xxx_os_windows 1
#endif
