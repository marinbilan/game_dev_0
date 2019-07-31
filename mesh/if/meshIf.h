#pragma once
#include <iostream>

#include "commonTypes.h"
#include "cameraIf.h"
#include "cameraDefault.h"

#include "shaderIf.h"
#include "defaultShader.h"
#include "gpuObjectIf.h"

namespace Mesh
{
class MeshIf
{
public:
	~MeshIf()
	{
	}

	virtual const std::string& getName() 
	{ 
		return "Error: MeshIf::getName() called from MeshIf!"; 
	}

	virtual void preInit() {};
	virtual void postInit() {};

	// Set
	virtual void setShader() {};

	// TODO: Remove this
	virtual void setTextureId(GLuint texId) {};

	// Get

	virtual void render(const glm::mat4& modelMatrix, GLuint VAO, GLuint VBO, GLuint IBO, GLuint numOfInds, const GPUObject::TextureStructure textureStruct) {};
	virtual void render(const glm::mat4& modelMatrix, const GPUObject::Mesh modelMesh, const GPUObject::TextureStructure textureStruct) {};

	virtual void render(const glm::mat4& modelMatrix, GLuint VBO, GLuint IBO, GLuint numOfInds) {};

	virtual void cmdPrompt(const std::string& arg0)
	{
	}
};
}