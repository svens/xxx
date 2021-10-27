#pragma once // -*- C++ -*-

#include <catch2/catch_test_macros.hpp>
#include <string>


namespace xxx_test {


inline std::string case_name ()
{
	return Catch::getResultCapture().getCurrentTestName();
}


bool has_ci_environment_variable ();
inline const bool on_ci = has_ci_environment_variable();


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
