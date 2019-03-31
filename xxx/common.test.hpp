#pragma once

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>
#include <string>


namespace xxx_test {


inline std::string case_name ()
{
  return Catch::getResultCapture().getCurrentTestName();
}


bool on_appveyor_ci ();
bool on_travis_ci ();
inline const bool on_ci = on_appveyor_ci() || on_travis_ci();


struct bad_alloc_once
{
  static inline bool fail = false;

  bad_alloc_once () noexcept
  {
    fail = true;
  }

  ~bad_alloc_once () noexcept
  {
    fail = false;
  }
};


} // namespace xxx_test
