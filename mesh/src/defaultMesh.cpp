#include "defaultMesh.h"

#include "error.h"
#include "factory.h"


Mesh::DefaultMesh::DefaultMesh(Common::Error& err, const std::string& name) : m_name(name)
{
	std::cout << "DefaultMesh created!" << std::endl;
}


Mesh::DefaultMesh::~DefaultMesh()
{
	std::cout << "DefaultMesh destructor called!" << std::endl;
}


void Mesh::DefaultMesh::render()
{
	std::cout << "Mesh::DefaultMesh::render() : " << m_name << std::endl;
	defaultShaderIf = Common::Factory::getInstance().getShaderIf("smartShader_0");

	std::cout << " TEST TEST: " << defaultShaderIf->getId() << std::endl;
};


void Mesh::DefaultMesh::preInit()
{

}


void Mesh::DefaultMesh::postInit()
{
	std::cout << "postInit function called!" << std::endl;
}


void Mesh::DefaultMesh::cmdPrompt(const std::string& arg0)
{
	std::cout << "cmdPrompt object: " << m_name << " called with arg: " << arg0 << std::endl;
}
