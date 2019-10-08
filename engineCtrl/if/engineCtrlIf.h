#pragma once
#include <iostream>
#include <string>

#include "glew.h"
#include "glfw3.h"

#include "commonTypes.h"
#include "database.h"
#include "cmdPrompt.h"

#include "initIf.h"
#include "initDefault.h"


namespace EngineCtrl
{
class EngineCtrlIf
{
public:
	~EngineCtrlIf()
	{
	}

	virtual void preInit() {};
	virtual void postInit() {};

	// ========================================================================================
	// NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION
	// ========================================================================================
	virtual void preInitialization() {};
	virtual void postInitialization() {};

	virtual void databaseInit(const std::string& dbName) {};

	virtual void glfwInitialization() {};

	// Prepare and Render
	virtual void gameLoop() {};

	virtual void render() {};
};
} // End of Namespace