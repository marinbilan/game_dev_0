#pragma once
#include <iostream>
#include <vector>
#include <memory>

#include "commonTypes.h"

#include "gpuObjectIf.h"
#include "cameraIf.h"
#include "LightIf.h"

#include "shaderIf.h"

namespace Model
{
class ModelIf
{
public:
	~ModelIf()
	{
	}

	virtual void preInit() {};
	virtual void postInit() {};

	// ========================================================================================
    // NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION
    // ========================================================================================
	virtual void preInitialization() {};
	virtual void postInitialization() {};

	virtual const std::string& getName() 
	{ 
		return "Not implemented in ModelIf"; 
	}

	virtual void render() {};

	virtual void cmdPrompt(const std::string& arg0)
	{
	}
};
}