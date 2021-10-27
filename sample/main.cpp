#include <iostream>
#include <xxx/error.hpp>


int main ()
{
	std::cout << xxx::error_category().name() << '\n';
	return EXIT_SUCCESS;
}
