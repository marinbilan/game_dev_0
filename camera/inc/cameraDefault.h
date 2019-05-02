#pragma once

#include "cameraIf.h"
#include "error.h"

namespace Camera
{
class CameraDefault : public CameraIf
{
public:
	CameraDefault(Common::Error& err, const std::string& name);

	~CameraDefault();

	const std::string& getName() 
	{ 
		return m_name; 
	}
	void preInit();
	void postInit();

	// FUNCTIONs
	virtual glm::vec3 getcameraPosition();
	
	virtual GLfloat getcameraPositionX();
	virtual GLfloat getcameraPositionY();
	virtual GLfloat getcameraPositionZ();
	//virtual void setcameraPosition(glm::vec3 _position);

	virtual void invertCameraDown();
	virtual void invertCameraUp();
	virtual void setcameraPositionY(GLfloat _positionY);

	virtual void moveForward(GLfloat deltaTime);
	virtual void moveBack(GLfloat deltaTime);
	virtual void strafeLeft(GLfloat deltaTime);
	virtual void strafeRight(GLfloat deltaTime);

	virtual void camFront(glm::vec3 _cameraFront);

	virtual void stopTranslate();
	virtual void invertCameraY();
	virtual void updateCameraPosition();
	// virtual void updateCameraUniform(Shaders::ShadersIf::ShadersIf* shader);
	// virtual void updateCameraUniformInv(Shaders::ShadersIf::ShadersIf* shader);
	//
	// NEW
	//
	
	virtual glm::mat4 getViewMatrix();
	virtual glm::mat4 getInvViewMatrix();
	virtual void invertCameraMatrix();
	// OPERATORs


private:
	std::string m_name;

// MODEL VARIABLEs
glm::mat4 viewMatrix;
glm::mat4 viewMatrixInv;


glm::vec3 cameraPos;
glm::vec3 cameraFront;
glm::vec3 cameraUp;

GLfloat distance;
};
}