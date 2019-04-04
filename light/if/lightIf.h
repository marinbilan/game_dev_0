#pragma once
#include <iostream>


namespace Light
{
class LightIf
{
public:
	~LightIf()
	{
		std::cout << "LightIf destructor called!" << std::endl;
	}

	virtual void preInit() {};

	virtual void postInit() {};

};
}