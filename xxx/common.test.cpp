#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <xxx/common.test.hpp>
#include <cstdlib>


#if __xxx_os_linux || __xxx_os_macos

#include <cstdio>
#include <dlfcn.h>

auto get_libc_malloc ()
{
  if (auto fn = dlsym(RTLD_NEXT, "malloc"))
  {
    return reinterpret_cast<void*(*)(size_t)>(fn);
  }
  std::terminate();
}

void *malloc (size_t size)
{
  auto libc_malloc = get_libc_malloc();

  if (xxx_test::enforce_bad_alloc::fail)
  {
    xxx_test::enforce_bad_alloc::fail = false;
    return nullptr;
  }

  return (*libc_malloc)(size);
}

#endif


void *operator new (size_t size)
{
  if (xxx_test::enforce_bad_alloc::fail)
  {
    xxx_test::enforce_bad_alloc::fail = false;
    throw std::bad_alloc();
  }
  return std::malloc(size);
}


void operator delete (void *ptr) noexcept
{
  std::free(ptr);
}


void operator delete (void *ptr, size_t) noexcept
{
  std::free(ptr);
}
