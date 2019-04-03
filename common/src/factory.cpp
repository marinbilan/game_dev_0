#include "factory.h"


// Methods 
void Common::Factory::showMeSeededClasses()
{
	mapType::iterator it;
	for (it = m_classesMap.begin(); it != m_classesMap.end(); ++it)
	{
		std::cout << " - " << it->first << std::endl;
	}
}

void Common::Factory::showMeModelIfObjects()
{
	for (auto it = m_vecOfModelIf.begin(); it != m_vecOfModelIf.end(); ++it)
	{
		std::cout << " Model object: " << (*it)->getName() << std::endl;

	}
}

void Common::Factory::showMeMeshIfObjects()
{
	for (auto it = m_vecOfMeshIf.begin(); it != m_vecOfMeshIf.end(); ++it)
	{
		std::cout << " Mesh object: " << (*it)->getName() << std::endl;

	}
}

// Container Stuff
// STORE
void Common::Factory::storeInContainer(std::shared_ptr<Model::StaticModel>& arg0)
{
	m_vecOfModelIf.push_back(std::dynamic_pointer_cast<Model::ModelIf>(arg0));
}

void Common::Factory::storeInContainer(std::shared_ptr<Mesh::DefaultMesh>& arg0)
{
	m_vecOfMeshIf.push_back(std::dynamic_pointer_cast<Mesh::MeshIf>(arg0));
}

// GET
std::shared_ptr<Model::ModelIf>& Common::Factory::getModelIf(const std::string& arg0)
{
	for (auto it = m_vecOfModelIf.begin(); it != m_vecOfModelIf.end(); ++it)
	{
		if (!(*it)->getName().compare(arg0))
		{
			std::cout << "- FOUND -" << (*it)->getName() << " number of shared objects " << (*it).use_count() << std::endl;
			return *it;
		}
	}

	return errorModel;
}

std::shared_ptr<Mesh::MeshIf>& Common::Factory::getMeshIf(const std::string& arg0)
{
	for (auto it = m_vecOfMeshIf.begin(); it != m_vecOfMeshIf.end(); ++it)
	{
		if (!(*it)->getName().compare(arg0))
		{
			std::cout << "- FOUND -" << (*it)->getName() << " number of shared objects " << (*it).use_count() << std::endl;
			return *it;
		}
	}

	return errorMesh;
}

