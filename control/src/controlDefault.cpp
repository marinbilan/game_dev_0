#include "controlDefault.h"
#include "error.h"


Control::ControlDefault::ControlDefault(Common::Error& err, const std::string& name) : m_name(name)
{
	std::cout << "ControlDefault created!" << std::endl;
}


Control::ControlDefault::~ControlDefault()
{
	std::cout << "ControlDefault destructor called!" << std::endl;
}


void Control::ControlDefault::preInit()
{

}


void Control::ControlDefault::postInit()
{
	std::cout << "postInit function called!" << std::endl;
}



//
// Camera (View)
//
/*
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 front;

GLfloat yaw = -90.0f;
GLfloat pitch = 0.0f;
GLfloat savePitch = 0.0f;
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;

bool keys[1024];
bool firstMouse = true;
//
// KEYBOARD
//
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_C)
	{
		char c;
		std::cout << "> ";
		std::cin >> c;
	}
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}
//
// MOUSE
//
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
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

	camera->camFront(cameraFront);
	camera->updateCameraPosition();
}

void do_movement()
{
	if (keys[GLFW_KEY_W])
	{
		camera->moveForward(deltaTime);
		camera->updateCameraPosition();
	}
	if (keys[GLFW_KEY_S])
	{
		camera->moveBack(deltaTime);
		camera->updateCameraPosition();
	}
	if (keys[GLFW_KEY_A])
	{
		camera->strafeLeft(deltaTime);
		camera->updateCameraPosition();
	}
	if (keys[GLFW_KEY_D])
	{
		camera->strafeRight(deltaTime);
		camera->updateCameraPosition();
	}
}
*/