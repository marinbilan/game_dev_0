#pragma once
#include <iostream>

#include "glm/vec3.hpp"

namespace Light
{
class LightIf
{
public:
	~LightIf()
	{
		std::cout << "Error: LightIf::~LightIf() called from LightIf!" << '\n';
	}

	virtual const std::string& getName()
	{
		return "Not implemented in Light";
	}

	virtual void preInit() {};
	virtual void postInit() {};

	virtual glm::vec3& getLightPosition() 
	{ 
		return dummy;
	};

	virtual glm::vec3& getLightColors()
	{
		return dummy;
	};

private:
	glm::vec3 dummy = glm::vec3(0, 0, 0);
};
} // End of namespace