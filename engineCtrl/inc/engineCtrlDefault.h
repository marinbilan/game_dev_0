#pragma once
#include "engineCtrlIf.h"


namespace EngineCtrl
{
class EngineCtrlDefault : public EngineCtrlIf
{
public:
	EngineCtrlDefault(const std::string& name);
	~EngineCtrlDefault();

	void preInitialization();
	void postInitialization();

	// Database init before preInit and postInit
	void databaseInit(const std::string& dbName);

	void glfwInitialization();

	// Render
	void gameLoop();

	void render();

private:
std::string m_name;

std::unique_ptr<Init::InitIf> m_defaultInit0;

std::unique_ptr<Common::CmdPrompt> m_cmdPrompt0;

GLFWwindow* m_window;

GLfloat m_deltaTime;
GLfloat m_lastFrame;
};
}