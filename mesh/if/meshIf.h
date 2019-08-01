#pragma once
#include <iostream>

#include "commonTypes.h"
// TODO: Remove
#include "cameraIf.h"
#include "cameraDefault.h"
// ----

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

	virtual void render(const glm::mat4& modelMatrix, const GPUObject::Mesh modelMesh, const GPUObject::TextureStructure textureStruct) {};

	virtual void cmdPrompt(const std::string& arg0)
	{
	}
};
}