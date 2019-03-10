#pragma once

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>
#include <xxx/config.hpp>


namespace xxx_test {


struct enforce_bad_alloc
{
  static inline bool fail = false;

  enforce_bad_alloc () noexcept
  {
    fail = true;
  }

  ~enforce_bad_alloc () noexcept
  {
    fail = false;
  }
};


} // namespace xxx_test
