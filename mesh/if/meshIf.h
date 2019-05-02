#pragma once
#include <iostream>

#include "shaderIf.h"
#include "cameraIf.h"
#include "cameraDefault.h"

namespace Mesh
{
class MeshIf
{
public:
	~MeshIf()
	{
		std::cout << "MeshIf destructor called!" << std::endl;
	}

	virtual const std::string& getName() 
	{ 
		return "not implemented in MeshIf"; 
	}

	virtual void preInit() {};
	virtual void postInit() {};

	virtual void setVBO(GLuint VBO) {};
	virtual void setIBO(GLuint IBO) {};
	virtual void setNumOfInd(GLuint numOfInd) {};

	virtual void render() {};

	// Setters
	virtual void setShader(const std::shared_ptr<Shader::ShaderIf>& shaderIf) {};
	virtual void setCamera(const std::shared_ptr<Camera::CameraIf>& cameraIf) {};

	virtual void setTextureId(GLuint texId) {};

	virtual void cmdPrompt(const std::string& arg0)
	{
		std::cout << "Error: Not implemented function - calling from ComminIf" << std::endl;
	}
};
}