#pragma once
#include <iostream>


namespace Light
{
class LightIf
{
public:
	~LightIf()
	{
		std::cout << "Error: LightIf::~LightIf() called from LightIf!" << '\n';
	}

	virtual void preInit() {};
	virtual void postInit() {};
};
} // End of namespace