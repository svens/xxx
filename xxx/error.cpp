#include <xxx/error.hpp>
#include <string>


__xxx_begin


namespace {

constexpr std::string_view as_view (errc ec) noexcept
{
	switch (ec)
	{
		#define __xxx_errc_case(code, message) case xxx::errc::code: return message;
		__xxx_errc(__xxx_errc_case)
		#undef __xxx_errc_case
	}
	return "unknown";
}

} // namespace


const std::error_category &error_category () noexcept
{
	struct error_category_impl: std::error_category
	{
		[[nodiscard]] const char *name () const noexcept final
		{
			return "xxx";
		}

		[[nodiscard]] std::string message (int ec) const final
		{
			return std::string{as_view(static_cast<errc>(ec))};
		}
	};
	static const error_category_impl impl{};
	return impl;
}


__xxx_end
