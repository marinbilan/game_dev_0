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


int main ()
{
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 8);

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
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

	EngineCtrl::EngineCtrlDefault engineCtrl0(err, "engineControl");
	engineCtrl0.preInit();
	engineCtrl0.postInit();
	
	std::cout << " ----> Render from main()" << '\n';
	Common::Factory::getInstance().getModelIf("smartModel_0")->render();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();








	return 0;
};