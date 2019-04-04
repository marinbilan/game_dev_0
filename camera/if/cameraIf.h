#pragma once
#include <iostream>

#include "glew.h"
#include "glfw3.h"


namespace Camera
{
class CameraIf
{
public:
	~CameraIf()
	{
		std::cout << "CameraIf destructor called!" << std::endl;
	}

	virtual void preInit() {};
	virtual void postInit() {};

	// FUNCTIONs
	// virtual glm::vec3 getcameraPosition() { return glm::vec3(1.0f, 1.0f, 1.0f); };
	virtual GLfloat getcameraPositionX() { return 0; };
	virtual GLfloat getcameraPositionY() { return 0; };
	virtual GLfloat getcameraPositionZ() { return 0; };
	//virtual void setcameraPosition(glm::vec3 _position) {};
	virtual void invertCameraDown() {};
	virtual void invertCameraUp() {};
	virtual void setcameraPositionY(GLfloat _positionY) {};

	virtual void moveForward(GLfloat deltaTime) {};
	virtual void moveBack(GLfloat deltaTime) {};
	virtual void strafeLeft(GLfloat deltaTime) {};
	virtual void strafeRight(GLfloat deltaTime) {};

	// virtual void camFront(glm::vec3 _cameraFront) {};

	virtual void stopTranslate() {};
	virtual void invertCameraY() {};
	virtual void updateCameraPosition() {};
	// virtual void updateCameraUniform(Shaders::ShadersIf::ShadersIf* shader) {};
	// virtual void updateCameraUniformInv(Shaders::ShadersIf::ShadersIf* shader) {};
	// NEW
	// virtual glm::mat4 getViewMatrix() { return glm::mat4(1.0f); }
	// virtual glm::mat4 getInvViewMatrix() { return glm::mat4(1.0f); }
	virtual void invertCameraMatrix() {}
	// OPERATORs	
};
}