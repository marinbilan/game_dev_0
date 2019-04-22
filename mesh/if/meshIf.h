#pragma once
#include <iostream>

#include "shaderIf.h"
// #include "defaultShader.h"

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

	virtual void render() {};

	// Setters
	virtual void setShader(const std::shared_ptr<Shader::ShaderIf>& shaderIf) {};
	virtual void setTextureId(GLuint texId) {};

	virtual void cmdPrompt(const std::string& arg0)
	{
		std::cout << "Error: Not implemented function - calling from ComminIf" << std::endl;
	}
};
}