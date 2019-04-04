#include "cameraDefault.h"
#include "error.h"


Camera::CameraDefault::CameraDefault(Common::Error& err, const std::string& name) : m_name(name)
{
	std::cout << "CameraDefault created!" << std::endl;
}


Camera::CameraDefault::~CameraDefault()
{
	std::cout << "TemplateDefault destructor called!" << std::endl;
}


void Camera::CameraDefault::preInit()
{

}


void Camera::CameraDefault::postInit()
{
	std::cout << "postInit function called!" << std::endl;
}

/*
Camera::Camera::Camera(glm::vec3 _cameraPos, glm::vec3 _cameraFront, glm::vec3 _cameraUp) :
	cameraPos(_cameraPos), cameraFront(_cameraFront), cameraUp(_cameraUp)
{
	//
	// INITIALIZE CAMERA POSITION
	//
	// cameraPos =   glm::vec3(0.0f, 0.0f, 15.0f);
	// cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	// cameraUp =    glm::vec3(0.0f, 1.0f, 0.0f);

	std::cout << "Camera created!" << std::endl;
}

Camera::Camera::~Camera()
{
	std::cout << "Camera destructor called!" << std::endl;
}
//
// FUNCTION(s)
// 
glm::vec3 Camera::Camera::getcameraPosition()
{
	return cameraPos;
}

GLfloat Camera::Camera::getcameraPositionX()
{
	return cameraPos.x;
}

GLfloat Camera::Camera::getcameraPositionY()
{
	return cameraPos.y;
}

GLfloat Camera::Camera::getcameraPositionZ()
{
	return cameraPos.z;
}

//void Camera::Camera::setcameraPosition(glm::vec3 _position)
//{
//	cameraPos = _position;
//}
//
void Camera::Camera::setcameraPositionY(GLfloat _positionY)
{
	cameraPos.y = _positionY;
}

void Camera::Camera::moveForward(GLfloat deltaTime)
{
	GLfloat cameraSpeed = 17.0f * deltaTime;
	cameraPos += cameraSpeed * cameraFront;
}

void Camera::Camera::moveBack(GLfloat deltaTime)
{
	GLfloat cameraSpeed = 17.0f * deltaTime;
	cameraPos -= cameraSpeed * cameraFront;
}

void Camera::Camera::strafeLeft(GLfloat deltaTime)
{
	GLfloat cameraSpeed = 17.0f * deltaTime;
	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::Camera::strafeRight(GLfloat deltaTime)
{
	GLfloat cameraSpeed = 17.0f * deltaTime;
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::Camera::camFront(glm::vec3 _cameraFront)
{
	cameraFront = _cameraFront;
}

void Camera::Camera::stopTranslate()
{
	viewMatrix[3][0] = 0;
	viewMatrix[3][1] = 0;
	viewMatrix[3][2] = 0;
}

void Camera::Camera::invertCameraDown()
{
	distance = 2 * (cameraPos.y - 0.0f);
	setcameraPositionY(cameraPos.y - distance);
	cameraFront.y = -cameraFront.y;
	updateCameraPosition();
}

void Camera::Camera::invertCameraUp()
{
	cameraFront.y = -cameraFront.y;
	setcameraPositionY(cameraPos.y + distance);
	updateCameraPosition();
}

void Camera::Camera::invertCameraY()
{
	cameraFront.y = -cameraFront.y;
}

void Camera::Camera::updateCameraPosition()
{
	viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::Camera::updateCameraUniform(Shaders::ShadersIf::ShadersIf* shader)
{
	glUniformMatrix4fv(shader->getViewMatrixID(), 1, GL_FALSE, &viewMatrix[0][0]);

	glm::mat4 viewMatrixInv = glm::inverse(viewMatrix);
	glUniformMatrix4fv(shader->getViewMatrixInvID(), 1, GL_FALSE, &viewMatrixInv[0][0]);
}

void Camera::Camera::updateCameraUniformInv(Shaders::ShadersIf::ShadersIf* shader)
{
	glUniformMatrix4fv(shader->getViewMatrixID(), 1, GL_FALSE, &viewMatrix[0][0]);

	glm::mat4 viewMatrixInv = glm::inverse(viewMatrix);
	glUniformMatrix4fv(shader->getViewMatrixInvID(), 1, GL_FALSE, &viewMatrixInv[0][0]);
}

// NEW

glm::mat4 Camera::Camera::getViewMatrix()
{
	return viewMatrix;
}

void Camera::Camera::invertCameraMatrix()
{
	viewMatrixInv = glm::inverse(viewMatrix);
}

glm::mat4 Camera::Camera::getInvViewMatrix()
{
	return viewMatrixInv;
}
*/