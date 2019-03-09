#include <xxx/error.hpp>
#include <tests/common.hpp>


namespace {


TEST_CASE("error")
{
  SECTION("errc")
  {
    #define __xxx_errc_impl(code, message) xxx::errc::code,
    std::error_code ec = GENERATE(values({__xxx_errc(__xxx_errc_impl)}));
    #undef __xxx_errc_impl

    SECTION("message")
    {
      CHECK_FALSE(ec.message().empty());
      CHECK(ec.message() != "unknown");
      CHECK(ec.category() == xxx::error_category());
      CHECK(ec.category().name() == std::string{"xxx"});
    }
  }


  SECTION("unknown")
  {
    std::error_code ec = static_cast<xxx::errc>(0);
    CHECK(ec.message() == "unknown");
    CHECK(ec.category() == xxx::error_category());
    CHECK(ec.category().name() == std::string{"xxx"});
  }
}


} // namespace
