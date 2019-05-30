#pragma once
#include <iostream>

#include "commonTypes.h"
#include "cameraIf.h"
#include "cameraDefault.h"

#include "shaderIf.h"
#include "defaultShader.h"


namespace Mesh
{
class MeshIf
{
public:
	~MeshIf()
	{
		std::cout << "MeshIf::~MeshIf() destructor called!" << '\n';
	}

	virtual const std::string& getName() 
	{ 
		return "Error: MeshIf::getName() called from MeshIf!"; 
	}

	virtual void preInit() {};
	virtual void postInit() {};

	// Get

	// Set
	//virtual void setShader(const std::shared_ptr<Shader::ShaderIf>& shaderIf) {}; // TODO: Remove
	virtual void setShader() {};

	virtual void setCamera(const std::shared_ptr<Camera::CameraIf>& cameraIf) {};

	// TODO: Remove
	virtual void setVBO(GLuint VBO) {};
	virtual void setIBO(GLuint IBO) {};
	virtual void setNumOfInd(GLuint numOfInd) {};

	virtual void setTextureId(GLuint texId) {};

	virtual void render(const glm::mat4& modelMatrix) {};

	virtual void cmdPrompt(const std::string& arg0)
	{
		std::cout << "Error: MeshIf::cmdPrompt() called from MeshIf!" << '\n';
	}
};
}