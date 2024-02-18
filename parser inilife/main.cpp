#include "IniParser.h"
#include <iostream>

int main()
{
	try
	{
		iniParser pars1("test.ini");
		std::cout << pars1.getValue<float>("Section1", "var1") << std::endl;
	}
	catch (std::runtime_error ex)
	{
		std::cout << ex.what();
	}
	return 0;
}