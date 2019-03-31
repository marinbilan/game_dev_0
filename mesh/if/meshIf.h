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

	virtual const std::string& getName() { return "not implemented in MeshIf"; }
};
}