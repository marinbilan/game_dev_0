#pragma once

#include "cameraIf.h"
#include "error.h"


namespace Camera
{
class CameraDefault : public CameraIf
{
public:
	CameraDefault(Common::Error& err, const std::string& name);

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

	// OPERATORs

private:
std::string m_name;

glm::vec3 m_cameraPos;
glm::vec3 m_cameraFront;
glm::vec3 m_cameraUp;

glm::mat4 m_viewMatrix;
glm::mat4 m_viewMatrixInv;
};
} // End of namespace