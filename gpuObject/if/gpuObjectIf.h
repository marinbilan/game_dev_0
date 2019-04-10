#pragma once
#include <iostream>

#include "glew.h"

namespace GPUObject
{
class GPUObjectIf
{
public:
	~GPUObjectIf()
	{
		std::cout << "GPUObjectIf destructor called!" << '\n';
	}

	virtual const std::string& getName()
	{
		return "not implemented in LoaderIf";
	}

	virtual void preInit() {};
	virtual void postInit() {};

	// modelGPUObjectIf
	virtual void setVAO(GLuint VAO)
	{
		std::cout << " ERROR: setVAO called from GUPObjectIf" << '\n';
	}

	virtual void setVBO(GLuint VBO)
	{
		std::cout << " ERROR: setVBO called from GUPObjectIf" << '\n';
	}

	virtual void setIBO(GLuint IBO)
	{
		std::cout << " ERROR: setIBO called from GUPObjectIf" << '\n';
	}

	virtual void info() {}
};
}