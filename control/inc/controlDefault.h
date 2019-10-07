#pragma once
#include "controlIf.h"

#include "camera.h"
#include "cameraDefault.h"

namespace Control
{

class ControlDefault : public ControlIf
{
public:
	ControlDefault(const std::string& name);
	ControlDefault(const std::string& dbPath, const std::string& name);

	~ControlDefault();

	const std::string& getName()
	{
		return m_name;
	}

	void preInit();
	void postInit();

	// ========================================================================================
    // NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION
    // ========================================================================================
	void preInitialization();
	void postInitialization();

	static void keyCallback(
		GLFWwindow* window,
		int key,
		int scancode,
		int action,
		int mods);

	static void mouseCallback(
		GLFWwindow* window,
		double xpos,
		double ypos);

	void updateCameraPosition(GLfloat deltaTime);

	void doCameraKeyboardMovement(GLfloat deltaTime);
	void doCameraMouseMovement();

private:
std::string m_dbPath;
std::string m_dbPathWithName;
std::string m_name;

std::shared_ptr<Camera::CameraIf> m_camera;
};
}