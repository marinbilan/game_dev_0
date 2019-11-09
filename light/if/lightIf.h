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
	}

	virtual const std::string& getName()
	{
		return "Not implemented in Light";
	}

	virtual void preInitialization() {};
	virtual void postInitialization() {};

	virtual glm::vec3& getLightPosition() 
	{ 
		return dummy;
	};

	virtual glm::vec3& getLightColors()
	{
		return dummy;
	};

	virtual void dump() {};
	virtual void cmdPrompt(const std::string& arg0) {};

private:
	glm::vec3 dummy = glm::vec3(0, 0, 0);
};
} // End of namespace