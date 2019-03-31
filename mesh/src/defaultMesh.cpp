#include "defaultMesh.h"
#include "error.h"


Mesh::DefaultMesh::DefaultMesh(Common::Error& err, const std::string& name) : m_name(name)
{
	std::cout << "DefaultMesh created!" << std::endl;
}


Mesh::DefaultMesh::~DefaultMesh()
{
	std::cout << "DefaultMesh destructor called!" << std::endl;
}


void Mesh::DefaultMesh::preInit()
{

}


void Mesh::DefaultMesh::postInit()
{
	std::cout << "postInit function called!" << std::endl;
}

