#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <xxx/common.test.hpp>
#include <xxx/__bits/build.hpp>
#include <cstdlib>


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
