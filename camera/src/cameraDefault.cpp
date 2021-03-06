#include "cameraDefault.h"
#include "factory.h"


Camera::CameraDefault::CameraDefault(const std::string& name) : 
	m_name(name),
	m_cameraPos(glm::vec3(0, 0, 0)),
	m_cameraFront(glm::vec3(0, 0, 1)),
	m_cameraUp(glm::vec3(0, 1, 0)),
	m_viewMatrix(glm::mat4(1.0f)),
	m_viewMatrixInv(glm::mat4(1.0f)),
	velocityFactor(17.0f)
{
	FACTORY.getLog()->LOGFILE(LOG "CameraDefault: " + m_name + " created.");
}


Camera::CameraDefault::CameraDefault(const std::string& dbPath, const std::string& name) :
	m_dbPath(dbPath),
	m_name(name),
	m_cameraPos(glm::vec3(0, 0, 0)),
	m_cameraFront(glm::vec3(0, 0, 1)),
	m_cameraUp(glm::vec3(0, 1, 0)),
	m_viewMatrix(glm::mat4(1.0f)),
	m_viewMatrixInv(glm::mat4(1.0f)),
	velocityFactor(17.0f)
{
	FACTORY.getLog()->LOGFILE(LOG "CameraDefault: " + m_name + " created.");

	m_dbPathWithName = m_dbPath + m_name + "_";
	std::cout << " CREATION INSTANCE - m_dbPathWithName: " << m_dbPathWithName << " modelName: " << m_name << '\n';
}


Camera::CameraDefault::~CameraDefault()
{
}


void Camera::CameraDefault::preInitialization()
{
	// 1] Get Camera Position
	std::string dBKey = m_dbPathWithName + "cameraPosition";
	FACTORY.getDatabase()->getVec3(dBKey, m_cameraPos);

	// 2] Get Camera Front
	dBKey = m_dbPathWithName + "cameraFront";
	FACTORY.getDatabase()->getVec3(dBKey, m_cameraFront);

	// 3] Get Camera Up
	dBKey = m_dbPathWithName + "cameraUp";
	FACTORY.getDatabase()->getVec3(dBKey, m_cameraUp);

	m_viewMatrix = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);

	FACTORY.getLog()->LOGFILE(LOG "CameraDefault: " + m_name + " preInitialization().");
}


void Camera::CameraDefault::postInitialization()
{
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


// KeyBoard part
void Camera::CameraDefault::moveCameraForward(GLfloat deltaTime)
{
	GLfloat cameraSpeed = velocityFactor * deltaTime;
	m_cameraPos += cameraSpeed * m_cameraFront;
}


void Camera::CameraDefault::moveCameraBack(GLfloat deltaTime)
{
	GLfloat cameraSpeed = velocityFactor * deltaTime;
	m_cameraPos -= cameraSpeed * m_cameraFront;
}


void Camera::CameraDefault::moveCameraStrafeLeft(GLfloat deltaTime)
{
	GLfloat cameraSpeed = velocityFactor * deltaTime;
	m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
}


void Camera::CameraDefault::moveCameraStrafeRight(GLfloat deltaTime)
{
	GLfloat cameraSpeed = velocityFactor * deltaTime;
	m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
}


void Camera::CameraDefault::updateCameraPosition()
{
	m_viewMatrix = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
}


// Mouse part
void Camera::CameraDefault::cameraFront(glm::vec3 cameraFront)
{
	m_cameraFront = cameraFront;
}


void Camera::CameraDefault::dump()
{
	std::cout << "| Camera Name.......: " << m_name << '\n';
	std::cout << "|  Camera Position..: " << m_cameraPos[0] << " " << m_cameraPos[1] << " " << m_cameraPos[2] << '\n';
	std::cout << "|  Camera Front.....: " << m_cameraFront[0] << " " << m_cameraFront[1] << " " << m_cameraFront[2] << '\n';
	std::cout << "|  Camera Up........: " << m_cameraUp[0] << " " << m_cameraUp[1] << " " << m_cameraUp[2] << '\n';
	std::cout << "|  Camera Velocity..: " << velocityFactor << '\n';
}


void Camera::CameraDefault::cmdPrompt(const std::string& arg0)
{

}