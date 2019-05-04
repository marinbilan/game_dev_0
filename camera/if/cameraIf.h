#pragma once
#include <iostream>

#include "glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace Camera
{
class CameraIf
{
public:
	virtual ~CameraIf()
	{
		std::cout << "Error: CameraIf::~CameraIf() called from CameraIf!" << '\n';
	}

	virtual const std::string& getName()
	{
		return "Error: CameraIf::getName() called from CameraIf!";
	}

	virtual void preInit() {};
	virtual void postInit() {};

	// FUNCTIONs
	// Get
	virtual glm::mat4& getViewMatrix() 
	{ 
		std::cout << "Error: CameraIf::getViewMatrix() called from CameraIf!" << '\n';
		glm::mat4 tempMatrix = glm::mat4(1.0f);
		return tempMatrix;
	}

	virtual glm::mat4& getInvViewMatrix() 
	{
		std::cout << "Error: CameraIf::getInvViewMatrix() called from CameraIf!" << '\n';
		glm::mat4 tempMatrix = glm::mat4(1.0f);
		return tempMatrix;
	}

	// Set
	virtual void invertCameraMatrix() 
	{
		std::cout << "Error: CameraIf::invertCameraMatrix() called from CameraIf!" << '\n';
	}

	// OPERATORs	
};
} // End of namespace