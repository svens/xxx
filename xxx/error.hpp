#pragma once // -*- C++ -*-

/**
 * \file xxx/error.hpp
 * XXX library error codes
 */

#include <xxx/version.hpp>
#include <system_error>


__xxx_begin


#define __xxx_errc(Impl) \
	Impl(__0, "internal placeholder for not an error") \
	Impl(temporary_error, "temporary error")


/**
 * XXX error codes
 */
enum class errc: int
{
	#define __xxx_errc_list(code, message) code,
	__xxx_errc(__xxx_errc_list)
	#undef __xxx_errc_list
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
