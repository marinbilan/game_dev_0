#pragma once
#include <iostream>

#include "commonTypes.h"

#include "gpuObjectIf.h"
#include "meshIf.h"

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

	virtual const std::string& getName() 
	{ 
		return "Not implemented in ModelIf"; 
	}

	// virtual void connect() {};

	virtual void render() {};

	virtual void cmdPrompt(const std::string& arg0)
	{
	}
};
}