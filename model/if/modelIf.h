#pragma once
#include <iostream>


namespace Model
{
class ModelIf
{
public:
	~ModelIf()
	{
		std::cout << "ModelIf destructor called!" << std::endl;
	}

	virtual void preInit() {};

	virtual void postInit() {};

	virtual const std::string& getName() { return "not implemented in ModelIf"; }

	virtual void cmdPrompt(const std::string& arg0)
	{
		std::cout << "Error: Not implemented function - calling from ComminIf" << std::endl;
	}
};
}