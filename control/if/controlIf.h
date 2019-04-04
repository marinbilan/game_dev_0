#pragma once
#include <iostream>


namespace Control
{
class ControlIf
{
public:
	~ControlIf()
	{
		std::cout << "ControlIf destructor called!" << std::endl;
	}

	virtual void preInit() {};

	virtual void postInit() {};

};
}