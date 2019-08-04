#pragma once 
#include <iostream>
#include <ctime>

#include "commonTypes.h"
#include "error.h"

#include "engineCtrlIf.h"
#include "engineCtrlDefault.h"

#include "controlIf.h"
#include "controlDefault.h"

#include "glew.h"
#include "glfw3.h"

#include "factory.h"

// TEST
// Assimp
#include "Importer.hpp"
#include "postprocess.h"
#include "mesh.h"
#include "scene.h"

// GLM
#include "glm.hpp"
#include "gtc/matrix_transform.hpp" // For projection matrix

// FreeImage 
#include "FreeImage.h"


// Move to renderer
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

// 

int main (int argc, char** argv)
{
	// std::cout << "You have entered " << argc << " arguments:" << "\n";	
	// for (int i = 0; i < argc; ++i) std::cout << argv[i] << "\n";

	/* Initialize the library */
	if (!glfwInit()) return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 8);

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(1024, 768, "Hello World", NULL, NULL);
	if (!window)
	{
		// std::cout << "Error: Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, Control::ControlDefault::keyCallback); 
	glfwSetCursorPosCallback(window, Control::ControlDefault::mouseCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		// std::cout << "Failed to initialize GLEW" << std::endl;
	}

	// TODO: Remove this
	Common::Error err;


	// 1] Create Engine Control
	// ------------------------
	EngineCtrl::EngineCtrlDefault engineCtrl0(err, "engineControl");
	// Create Database
	engineCtrl0.databaseInit("sw/_db/database_0.txt");
	
	// Init
	engineCtrl0.preInit(); 
	engineCtrl0.postInit();
	// ------------------------
	
	// NEW STUFF TESTING
	/*std::string str;
	FACTORY.getDatabase()->setMember("object1", "member1", str);
	std::cout << str << "\n";*/

	// current date/time based on current system
	// time_t now = time(0);
	// convert now to string form
	/*char* dt = ctime(&now);
	std::string log0(dt);
	std::cout << "The local date and time is: " << log0 << std::endl;*/

	// Move to render class
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);


	std::shared_ptr<Control::ControlIf> control = FACTORY.getControlIf("smartControl_0");
	control->postInit();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		// Calculate Time Frame
		// ----
		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// ----

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_CLIP_DISTANCE0);


		// Camera movement
		control->updateCameraPosition(deltaTime);

		Common::Factory::getInstance().getModelIf("smartModel_0")->render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
};