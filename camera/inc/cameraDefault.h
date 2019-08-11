#pragma once

#include "cameraIf.h"


namespace Camera
{
class CameraDefault : public CameraIf
{
public:
	CameraDefault(const std::string& name);
	~CameraDefault();

	const std::string& getName() 
	{ 
		return m_name;
	}

	void preInit();
	void postInit();

	// Get
	glm::mat4& getViewMatrix();
	glm::mat4& getInvViewMatrix();

	// Set
	void invertCameraMatrix();

	// Keyboard part
	void moveCameraForward(GLfloat deltaTime);
	void moveCameraBack(GLfloat deltaTime);
	void moveCameraStrafeLeft(GLfloat deltaTime);
	void moveCameraStrafeRight(GLfloat deltaTime);

	// Mouse part
	void cameraFront(glm::vec3 cameraFront);

	void updateCameraPosition();

	// OPERATORs

private:
std::string m_name;

glm::vec3 m_cameraPos;
glm::vec3 m_cameraFront;
glm::vec3 m_cameraUp;

glm::mat4 m_viewMatrix;
glm::mat4 m_viewMatrixInv;

GLfloat velocityFactor;
};
} // End of namespace