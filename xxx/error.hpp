#pragma once

/**
 * \file xxx/error.hpp
 * XXX library error codes
 */

#include <xxx/config.hpp>
#include <system_error>


__xxx_begin


#define __xxx_errc(impl) \
  impl(temporary_error, "temporary error")


/**
 * XXX error codes
 */
enum class errc
{
  __xxx_errc_0 = 0,
  #define __xxx_errc_impl(code, message) code,
    __xxx_errc(__xxx_errc_impl)
  #undef __xxx_errc_impl
};


/**
 * Return XXX error category. The name() virtual function returns "xxx".
 */
const std::error_category &error_category () noexcept;


/**
 * Make std::error_code from error code \a ec
 */
inline std::error_code make_error_code (errc ec) noexcept
{
  return std::error_code(static_cast<int>(ec), error_category());
}


__xxx_end


namespace std {

template <>
struct is_error_code_enum<xxx::errc>
    : true_type
{ };

} // namespace std
