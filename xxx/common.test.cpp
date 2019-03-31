#define _CRT_SECURE_NO_WARNINGS
#define CATCH_CONFIG_RUNNER

#include <catch2/catch.hpp>
#include <xxx/common.test.hpp>
#include <cstdlib>


#if __xxx_os_windows && !NDEBUG

int report_hook (int report_type, char *message, int *return_value)
{
  static const char *level[] = { "WARN", "ERROR", "ASSERT" };
  printf("[%s] %s\n", level[report_type], message);
  *return_value = 0;
  return TRUE;
}

void set_report_hook ()
{
  _CrtSetReportHook(report_hook);
}

#else

void set_report_hook ()
{ }

#endif


int main (int argc, char *argv[])
{
  set_report_hook();
  return Catch::Session().run(argc, argv);
}


void *operator new (size_t size)
{
  if (xxx_test::bad_alloc_once::fail)
  {
    xxx_test::bad_alloc_once::fail = false;
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


namespace xxx_test {

bool on_appveyor_ci ()
{
  static const bool has_env = (std::getenv("APPVEYOR") != nullptr);
  return has_env;
}

bool on_travis_ci ()
{
  static const bool has_env = (std::getenv("TRAVIS") != nullptr);
  return has_env;
}

} // namespace xxx_test
