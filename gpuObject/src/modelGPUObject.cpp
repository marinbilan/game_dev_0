#include "modelGPUObject.h"

#include "factory.h"


GPUObject::ModelGPUObject::ModelGPUObject(const std::string& name) : m_name(name)
{
	FACTORY.getLog()->LOGFILE(LOG "ModelGPUObject: " + m_name + " created.");
}


GPUObject::ModelGPUObject::~ModelGPUObject()
{
}


const std::string& GPUObject::ModelGPUObject::getName()
{
	return m_name;
}


void GPUObject::ModelGPUObject::preInitialization()
{
}


void GPUObject::ModelGPUObject::postInitialization()
{
}


void GPUObject::ModelGPUObject::setMeshInVec(const MeshStructure& mesh)
{
	m_vecOfMeshes.push_back(mesh);
}


std::vector<GPUObject::MeshStructure>& GPUObject::ModelGPUObject::getMeshVec()
{
	return m_vecOfMeshes;
}


void GPUObject::ModelGPUObject::info()
{	
	std::cout << " modelGPUObject name: " << m_name << '\n';
	for (auto mesh : m_vecOfMeshes)
	{
		mesh.dump();
	}
}

