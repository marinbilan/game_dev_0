#pragma once
#include <iostream>

#include "glew.h"
#include "glfw3.h"

#include "glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace Camera
{
class CameraIf
{
public:
	virtual ~CameraIf()
	{
	}

	virtual const std::string& getName()
	{
		return returnErrorStr;
	}

	virtual void preInitialization() {};
	virtual void postInitialization() {};

	// FUNCTIONs
	virtual glm::mat4& getViewMatrix() 
	{ 
		glm::mat4 tempMatrix = glm::mat4(1.0f);
		return tempMatrix;
	}

	virtual glm::mat4& getInvViewMatrix() 
	{
		glm::mat4 tempMatrix = glm::mat4(1.0f);
		return tempMatrix;
	}

	virtual void invertCameraMatrix() {}

	// Keyboard part
	virtual void moveCameraForward(GLfloat deltaTime) {};
	virtual void moveCameraBack(GLfloat deltaTime) {};
	virtual void moveCameraStrafeLeft(GLfloat deltaTime) {};
	virtual void moveCameraStrafeRight(GLfloat deltaTime) {};

	// Mouse part
	virtual void cameraFront(glm::vec3 cameraFront) {};
	virtual void updateCameraPosition() {};

	virtual void dump() {};
	virtual void cmdPrompt(const std::string& arg0){}

private:
	std::string returnErrorStr = "Error: CameraIf::getName() called from CameraIf!";
};
} // End of namespace