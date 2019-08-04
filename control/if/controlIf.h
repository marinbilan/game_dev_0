#pragma once
#include <iostream>

#include "glew.h"
#include "glfw3.h"

namespace Control
{
class ControlIf
{
public:
	~ControlIf()
	{
	}

	virtual const std::string& getName()
	{
		return "Error: ControlIf::getName() called from ControlIf!";
	}

	virtual void preInit() {};
	virtual void postInit() {};

	virtual void updateCameraPosition(GLfloat deltaTime) {};

	virtual void doCameraKeyboardMovement(GLfloat deltaTime) {};
	virtual void doCameraMouseMovement() {};
};
}