#include "modelGPUObject.h"

#include "error.h"


GPUObject::ModelGPUObject::ModelGPUObject(const std::string& name) : m_name(name)
{
}


GPUObject::ModelGPUObject::~ModelGPUObject()
{
}


const std::string& GPUObject::ModelGPUObject::getName()
{
	return m_name;
}

// Preinit
void GPUObject::ModelGPUObject::preInit()
{
}

// Postinit
void GPUObject::ModelGPUObject::postInit()
{
}


void GPUObject::ModelGPUObject::setVAO(GLuint VAO)
{
	m_VAO = VAO;
}


void GPUObject::ModelGPUObject::setMeshInVec(const Mesh& mesh)
{
	m_vecOfMeshes.push_back(mesh);
}


GLuint GPUObject::ModelGPUObject::getVAO()
{
	return m_VAO;
}


std::vector<GPUObject::Mesh>& GPUObject::ModelGPUObject::getMeshVec()
{
	return m_vecOfMeshes;
}


void GPUObject::ModelGPUObject::info()
{	
}

