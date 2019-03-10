#include <xxx/error.hpp>
#include <xxx/config.hpp>
#include <string>


__xxx_begin


namespace {

constexpr std::string_view to_string_view (errc ec) noexcept
{
  switch (ec)
  {
    #define __xxx_errc_case(code, message) case xxx::errc::code: return message;
      __xxx_errc(__xxx_errc_case)
    #undef __xxx_errc_case

    default:
      return "unknown";
  };
}

} // namespace


const std::error_category &error_category () noexcept
{
  struct error_category_impl
    : public std::error_category
  {
    const char *name () const noexcept final
    {
      return "xxx";
    }

    std::string message (int ec) const final
    {
      return std::string{to_string_view(static_cast<errc>(ec))};
    }
  };
  static const error_category_impl impl{};
  return impl;
}


__xxx_end
