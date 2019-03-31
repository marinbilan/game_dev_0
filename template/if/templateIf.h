#pragma once
#include <iostream>


namespace Template
{
class TemplateIf
{
public:
	~TemplateIf()
	{
		std::cout << "TemplateIf destructor called!" << std::endl;
	}

	virtual void preInit() {};

	virtual void postInit() {};

};
}