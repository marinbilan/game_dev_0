#pragma once
#include "controlDefault.h"

#include "factory.h"


// ---- GLOBAL VARs ----
// KeyBoard
bool keys[1024];

// Mouse
bool firstMouse = true;
// ---- ----

GLfloat yaw = -90.0f;
GLfloat pitch = 0.0f;
// GLfloat savePitch = 0.0f;
GLuint WIDTH;
GLuint HEIGHT = 768;
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;

glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 front;
// ---- ----


Control::ControlDefault::ControlDefault(const std::string& dbPath, const std::string& name) : 
	m_dbPath(dbPath),
	m_name(name)
{
	FACTORY.getLog()->LOGFILE(LOG "ControlDefault: " + m_name + " created.");
	WIDTH = 1024;

	m_dbPathWithName = m_dbPath + m_name + "_";
	std::cout << " CREATION INSTANCE - m_dbPathWithName: " << m_dbPathWithName << " modelName: " << m_name << '\n';
}


Control::ControlDefault::~ControlDefault()
{
}


void Control::ControlDefault::preInitialization()
{
	std::cout << " preInitialization - m_dbPathWithName: " << m_dbPathWithName << " modelName: " << m_name << '\n';
}


void Control::ControlDefault::postInitialization()
{
	// 1] Get Camera to Control
	std::string dBKey = m_dbPathWithName + "cameraToControl";
	std::vector<std::string> cameraToControl;
	FACTORY.getDatabase()->getStringsFromDB(dBKey, cameraToControl);
	m_camera = FACTORY.getCameraIf(cameraToControl[0]);
}


void Control::ControlDefault::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}


void Control::ControlDefault::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to left
	lastX = xpos;
	lastY = ypos;

	GLfloat sensitivity = 0.05;	// Change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);

}


void Control::ControlDefault::updateCameraPosition(GLfloat deltaTime)
{
	doCameraKeyboardMovement(deltaTime);
	doCameraMouseMovement();

	m_camera->updateCameraPosition();
}


void Control::ControlDefault::doCameraKeyboardMovement(GLfloat deltaTime)
{
	if (keys[GLFW_KEY_W])
	{
		m_camera->moveCameraForward(deltaTime);
	}
	if (keys[GLFW_KEY_S])
	{
		m_camera->moveCameraBack(deltaTime);
	}
	if (keys[GLFW_KEY_A])
	{
		m_camera->moveCameraStrafeLeft(deltaTime);
	}
	if (keys[GLFW_KEY_D])
	{
		m_camera->moveCameraStrafeRight(deltaTime);
	}
}


void Control::ControlDefault::doCameraMouseMovement()
{
	m_camera->cameraFront(cameraFront);
}



