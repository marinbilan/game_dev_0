#include "modelGPUObject.h"

#include "factory.h"


GPUObject::ModelGPUObject::ModelGPUObject(const std::string& name) : m_name(name)
{
	FACTORY.getLog()->LOGFILE(LOG "ModelGPUObject: " + m_name + " created.");
}


GPUObject::ModelGPUObject::ModelGPUObject(const std::string& dbPath, const std::string& name) :
	m_dbPath(dbPath),
	m_name(name)
{
	m_dbPathWithName = m_dbPath + m_name + "_";
	std::cout << " CREATION INSTANCE - m_dbPathWithName: " << m_dbPathWithName << " modelName: " << m_name << '\n';
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


// ========================================================================================
// NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION
// ========================================================================================
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

