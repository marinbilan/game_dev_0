#pragma once
#include <iostream>


namespace Mesh
{
class MeshIf
{
public:
	~MeshIf()
	{
		std::cout << "MeshIf destructor called!" << std::endl;
	}

	virtual void preInit() {};
	virtual void postInit() {};

	virtual void render() {};

	virtual const std::string& getName() 
	{ 
		return "not implemented in MeshIf"; 
	}

	virtual void cmdPrompt(const std::string& arg0)
	{
		std::cout << "Error: Not implemented function - calling from ComminIf" << std::endl;
	}
};
}