#pragma once
#include <string>
#include <iostream>

namespace Common
{

class CommonIf
{
public:
	virtual ~CommonIf()
	{
		std::cout << "Calling CommonIf Destructor" << std::endl;
	}

	virtual const std::string& getName() { }
};

}