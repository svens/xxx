#include <xxx/error.hpp>
#include <xxx/common.test.hpp>
#include <catch2/generators/catch_generators_all.hpp>
#include <type_traits>


namespace {


TEST_CASE("error")
{
	#define __xxx_errc_value(code, message) xxx::errc::code,

	SECTION("errc")
	{
		std::error_code ec = GENERATE(values({__xxx_errc(__xxx_errc_value)}));
		CAPTURE(ec);

		SECTION("message")
		{
			CHECK_FALSE(ec.message().empty());
			CHECK(ec.message() != "unknown");
			CHECK(ec.category() == xxx::error_category());
			CHECK(ec.category().name() == std::string{"xxx"});
		}
	}


	SECTION("message_bad_alloc")
	{
		std::error_code ec = xxx::errc::__0;
		xxx_test::bad_alloc_once x;
		CHECK_THROWS_AS(ec.message(), std::bad_alloc);
	}


	SECTION("unknown")
	{
		std::error_code ec = static_cast<xxx::errc>(
			std::numeric_limits<std::underlying_type_t<xxx::errc>>::max()
		);
		CHECK(ec.message() == "unknown");
		CHECK(ec.category() == xxx::error_category());
		CHECK(ec.category().name() == std::string{"xxx"});
	}
}


} // namespace
