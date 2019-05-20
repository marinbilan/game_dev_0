#include <iostream>

#include "error.h"

#include "engineCtrlIf.h"
#include "engineCtrlDefault.h"

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


int main (int argc, char** argv)
{
	std::cout << "You have entered " << argc
		<< " arguments:" << "\n";

	for (int i = 0; i < argc; ++i)
		std::cout << argv[i] << "\n";

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 8);

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(1024, 768, "Hello World", NULL, NULL);
	if (!window)
	{
		std::cout << "Error: Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	// glfwSetKeyCallback(window, key_callback);
	// glfwSetCursorPosCallback(window, mouse_callback);
	// glfwSetCharModsCallback(window, characterModCallback);

	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
	}


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



	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_CLIP_DISTANCE0);

		Common::Factory::getInstance().getModelIf("smartModel_0")->render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();








	return 0;
};