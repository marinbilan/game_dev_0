#pragma once
#include <iostream>

#include "gpuObjectIf.h"
#include "meshIf.h"

namespace Model
{
class ModelIf
{
public:
	~ModelIf()
	{
		std::cout << "ModelIf destructor called!" << std::endl;
	}

	virtual void preInit() {};
	virtual void postInit() {};

	virtual void setGPUObject(const std::shared_ptr<GPUObject::GPUObjectIf>& gpuObjectIf) {};
	virtual void setMesh(const std::shared_ptr<Mesh::MeshIf>& meshIf) {};

	virtual void render() {};

	virtual const std::string& getName() 
	{ 
		return "not implemented in ModelIf"; 
	}

	virtual void cmdPrompt(const std::string& arg0)
	{
		std::cout << "Error: Not implemented function - calling from ComminIf" << std::endl;
	}
};
}