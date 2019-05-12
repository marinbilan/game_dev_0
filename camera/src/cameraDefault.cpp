#include "cameraDefault.h"


Camera::CameraDefault::CameraDefault(Common::Error& err, const std::string& name) : 
	m_name(name),
	m_cameraPos(glm::vec3(0, 0, 0)),
	m_cameraFront(glm::vec3(0, 0, 1)),
	m_cameraUp(glm::vec3(0, 1, 0)),
	m_viewMatrix(glm::mat4(1.0f)),
	m_viewMatrixInv(glm::mat4(1.0f))
{
	// Move to preInit (read from DB)
	m_cameraPos =   glm::vec3(375, 25, 420);
	m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	m_cameraUp =    glm::vec3(0.0f, 1.0f, 0.0f);

	m_viewMatrix = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
}


Camera::CameraDefault::~CameraDefault()
{
	std::cout << "Camera::CameraDefault::~CameraDefault() called!" << '\n';
}


void Camera::CameraDefault::preInit()
{
	std::cout << "Camera::CameraDefault::preInit() called!" << '\n';
}


void Camera::CameraDefault::postInit()
{
	std::cout << "Camera::CameraDefault::postInit() called!" << '\n';
}


glm::mat4& Camera::CameraDefault::getViewMatrix()
{
	return m_viewMatrix;
}


glm::mat4& Camera::CameraDefault::getInvViewMatrix()
{
	return m_viewMatrixInv;
}


void Camera::CameraDefault::invertCameraMatrix()
{
	m_viewMatrixInv = glm::inverse(m_viewMatrix);
}


