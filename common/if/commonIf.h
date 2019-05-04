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
		std::cout << "Error: CommonIf::~CommonIf() called from CommonIf!" << '\n';
	}

	virtual const std::string& getName() 
	{ 
		return "Error: CommonIf::~getName() called from CommonIf!"; 
	}
};

}