#include <iostream>
#include <xxx/error.hpp>


int main ()
{
	std::cout << xxx::error_category().name()
		<< ' ' << xxx::version_major
		<< '.' << xxx::version_minor
		<< '.' << xxx::version_patch
		<< " (" << xxx::version << ')'
		<< '\n';
	return EXIT_SUCCESS;
}
