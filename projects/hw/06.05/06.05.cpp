////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

////////////////////////////////////////////////////////////////////////////////

#include <boost/dll.hpp>

////////////////////////////////////////////////////////////////////////////////

int main()
{
//  ----------------------------------------------------------------------------

	std::string version;
	std::cout << "Enter library version (v1 or v2): ";
	std::cin >> version;

//  ----------------------------------------------------------------------------

	std::string library_path;
	if (version == "v1")
	{
		library_path = "libshared_v1";
	}
	else if (version == "v2")
	{
		library_path = "libshared_v2";
	}
	else
	{
		std::cerr << "Invalid version. Please enter 'v1' or 'v2'.\n";
		return 1;
	}

//  ----------------------------------------------------------------------------

	try
	{
		auto test_function = boost::dll::import_symbol < void() > (
			library_path,
			"test"
		);

		test_function();
	}
	catch (std::exception const & e)
	{
		std::cerr << "Error loading library: " << e.what() << "\n";
		return 1;
	}

//  ----------------------------------------------------------------------------

	return 0;
}

////////////////////////////////////////////////////////////////////////////////