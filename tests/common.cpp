#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <tests/common.hpp>
#include <cstdlib>


#if __xxx_os_linux || __xxx_os_macos

#include <cstdio>
#include <dlfcn.h>

void *malloc (size_t size)
{
  static void *(*libc_malloc)(size_t) = nullptr;

  if (!libc_malloc)
  {
    libc_malloc = (decltype(libc_malloc))dlsym(RTLD_NEXT, "malloc");
    if (!libc_malloc)
    {
      std::terminate();
    }
  }

  if (!xxx_test::enforce_bad_alloc::fail)
  {
    return (*libc_malloc)(size);
  }

  return nullptr;
}

#endif


void *operator new (size_t size)
{
  if (!xxx_test::enforce_bad_alloc::fail)
  {
    return std::malloc(size);
  }
  throw std::bad_alloc();
}


void operator delete (void *ptr) noexcept
{
  std::free(ptr);
}


void operator delete (void *ptr, size_t) noexcept
{
  std::free(ptr);
}
