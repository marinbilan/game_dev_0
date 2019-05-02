#include "cameraDefault.h"
#include "error.h"


Camera::CameraDefault::CameraDefault(Common::Error& err, const std::string& name) : m_name(name)
{
	std::cout << " +++++++++++++++++++++++ CameraDefault created!" << std::endl;
	cameraPos =   glm::vec3(375, 25, 420);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp =    glm::vec3(0.0f, 1.0f, 0.0f);

	viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	std::cout << "  ----- matrix: " << viewMatrix[0][0] << " ";
	std::cout << "  ----- matrix: " << viewMatrix[0][1] << " ";
	std::cout << "  ----- matrix: " << viewMatrix[0][2] << " ";
	std::cout << "  ----- matrix: " << viewMatrix[0][3] << std::endl;

	std::cout << "  ----- matrix: " << viewMatrix[1][0] << " ";
	std::cout << "  ----- matrix: " << viewMatrix[1][1] << " ";
	std::cout << "  ----- matrix: " << viewMatrix[1][2] << " ";
	std::cout << "  ----- matrix: " << viewMatrix[1][3] << std::endl;

	std::cout << "  ----- matrix: " << viewMatrix[2][0] << " ";
	std::cout << "  ----- matrix: " << viewMatrix[2][1] << " ";
	std::cout << "  ----- matrix: " << viewMatrix[2][2] << " ";
	std::cout << "  ----- matrix: " << viewMatrix[2][3] << std::endl;

	std::cout << "  ----- matrix: " << viewMatrix[3][0] << " ";
	std::cout << "  ----- matrix: " << viewMatrix[3][1] << " ";
	std::cout << "  ----- matrix: " << viewMatrix[3][2] << " ";
	std::cout << "  ----- matrix: " << viewMatrix[3][3] << std::endl;
	// updateCameraPosition();
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
Camera::CameraDefault::CameraDefault(glm::vec3 _cameraPos, glm::vec3 _cameraFront, glm::vec3 _cameraUp) :
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
*/

//
// FUNCTION(s)
// 
glm::vec3 Camera::CameraDefault::getcameraPosition()
{
	return cameraPos;
}

GLfloat Camera::CameraDefault::getcameraPositionX()
{
	return cameraPos.x;
}

GLfloat Camera::CameraDefault::getcameraPositionY()
{
	return cameraPos.y;
}

GLfloat Camera::CameraDefault::getcameraPositionZ()
{
	return cameraPos.z;
}

//void Camera::Camera::setcameraPosition(glm::vec3 _position)
//{
//	cameraPos = _position;
//}
//
void Camera::CameraDefault::setcameraPositionY(GLfloat _positionY)
{
	cameraPos.y = _positionY;
}

void Camera::CameraDefault::moveForward(GLfloat deltaTime)
{
	GLfloat cameraSpeed = 17.0f * deltaTime;
	cameraPos += cameraSpeed * cameraFront;
}

void Camera::CameraDefault::moveBack(GLfloat deltaTime)
{
	GLfloat cameraSpeed = 17.0f * deltaTime;
	cameraPos -= cameraSpeed * cameraFront;
}

void Camera::CameraDefault::strafeLeft(GLfloat deltaTime)
{
	GLfloat cameraSpeed = 17.0f * deltaTime;
	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::CameraDefault::strafeRight(GLfloat deltaTime)
{
	GLfloat cameraSpeed = 17.0f * deltaTime;
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::CameraDefault::camFront(glm::vec3 _cameraFront)
{
	cameraFront = _cameraFront;
}

void Camera::CameraDefault::stopTranslate()
{
	viewMatrix[3][0] = 0;
	viewMatrix[3][1] = 0;
	viewMatrix[3][2] = 0;
}

void Camera::CameraDefault::invertCameraDown()
{
	distance = 2 * (cameraPos.y - 0.0f);
	setcameraPositionY(cameraPos.y - distance);
	cameraFront.y = -cameraFront.y;
	updateCameraPosition();
}

void Camera::CameraDefault::invertCameraUp()
{
	cameraFront.y = -cameraFront.y;
	setcameraPositionY(cameraPos.y + distance);
	updateCameraPosition();
}

void Camera::CameraDefault::invertCameraY()
{
	cameraFront.y = -cameraFront.y;
}

void Camera::CameraDefault::updateCameraPosition()
{
	viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

}
/*
void Camera::CameraDefault::updateCameraUniform(Shaders::ShadersIf::ShadersIf* shader)
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
*/
// NEW

glm::mat4 Camera::CameraDefault::getViewMatrix()
{
	return viewMatrix;
}

void Camera::CameraDefault::invertCameraMatrix()
{
	viewMatrixInv = glm::inverse(viewMatrix);
}

glm::mat4 Camera::CameraDefault::getInvViewMatrix()
{
	return viewMatrixInv;
}
