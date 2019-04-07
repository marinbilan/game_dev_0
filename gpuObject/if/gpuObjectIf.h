#pragma once
#include <iostream>


namespace GPUObject
{
class GPUObjectIf
{
public:
	~GPUObjectIf()
	{
		std::cout << "GPUObjectIf destructor called!" << std::endl;
	}

	virtual const std::string& getName()
	{
		return "not implemented in LoaderIf";
	}

	virtual void preInit() {};
	virtual void postInit() {};

};
}