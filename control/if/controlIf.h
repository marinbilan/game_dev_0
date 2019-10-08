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
		return returnErrorStr;
	}

	virtual void preInit() {};
	virtual void postInit() {};

	// ========================================================================================
    // NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION
    // ========================================================================================
	virtual void preInitialization() {};
	virtual void postInitialization() {};

	virtual void updateCameraPosition(GLfloat deltaTime) {};

	virtual void doCameraKeyboardMovement(GLfloat deltaTime) {};
	virtual void doCameraMouseMovement() {};

private:
	std::string returnErrorStr= "Error: ControlIf::getName() called from ControlIf!";
};
}