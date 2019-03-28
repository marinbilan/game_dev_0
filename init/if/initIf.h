#pragma once
#include <iostream>


namespace Init
{
class InitIf
{
public:
	~InitIf()
	{
		std::cout << "InitIf destructor called!" << std::endl;
	}

	virtual void preInit() {};

	virtual void postInit() {};

	virtual void registerClass() {};

	virtual void createDefaultObject() {};
};
}