#pragma once
#include <iostream>


namespace Shader
{
class ShaderIf
{
public:
	~ShaderIf()
	{
		std::cout << "ShaderIf destructor called!" << std::endl;
	}

	virtual const std::string& getName()
	{
		return "not implemented in MeshIf";
	}

	virtual int getId() { return 0; }

	virtual void preInit() {};
	virtual void postInit() {};

	virtual void cmdPrompt(const std::string& arg0)
	{
		std::cout << "Error: Not implemented function - calling from ComminIf" << std::endl;
	}
};
}