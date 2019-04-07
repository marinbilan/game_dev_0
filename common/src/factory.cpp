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

void Common::Factory::showMeShaderIfObjects()
{
	for (auto it = m_vecOfShaderIf.begin(); it != m_vecOfShaderIf.end(); ++it)
	{
		std::cout << " Shader object: " << (*it)->getName() << std::endl;

	}
}

void Common::Factory::showMeLoaderIfObjects()
{
	for (auto it = m_vecOfLoaderIf.begin(); it != m_vecOfLoaderIf.end(); ++it)
	{
		std::cout << " Loader object: " << (*it)->getName() << std::endl;

	}
}

void Common::Factory::showMeGPUIfObjects()
{
	for (auto it = m_vecOfGPUObjectIf.begin(); it != m_vecOfGPUObjectIf.end(); ++it)
	{
		std::cout << " GPU Object: " << (*it)->getName() << std::endl;

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

void Common::Factory::storeInContainer(std::shared_ptr<Shader::DefaultShader>& arg0)
{
	m_vecOfShaderIf.push_back(std::dynamic_pointer_cast<Shader::ShaderIf>(arg0));
}

// Loader
void Common::Factory::storeInContainer(std::shared_ptr<Loader::ModelLoader>& arg0)
{
	m_vecOfLoaderIf.push_back(std::dynamic_pointer_cast<Loader::LoaderIf>(arg0));
}

void Common::Factory::storeInContainer(std::shared_ptr<Loader::TextureLoader>& arg0)
{
	m_vecOfLoaderIf.push_back(std::dynamic_pointer_cast<Loader::LoaderIf>(arg0));
}
// GPU Objects
void Common::Factory::storeInContainer(std::shared_ptr<GPUObject::ModelGPUObject>& arg0)
{
	m_vecOfGPUObjectIf.push_back(std::dynamic_pointer_cast<GPUObject::GPUObjectIf>(arg0));
}

void Common::Factory::storeInContainer(std::shared_ptr<GPUObject::TextureGPUObject>& arg0)
{
	m_vecOfGPUObjectIf.push_back(std::dynamic_pointer_cast<GPUObject::GPUObjectIf>(arg0));
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

	// If can't find element in vector, return first
	return m_vecOfModelIf[0];
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

	// If can't find element in vector, return first
	return m_vecOfMeshIf[0];
}

std::shared_ptr<Shader::ShaderIf>& Common::Factory::getShaderIf(const std::string& arg0)
{
	for (auto it = m_vecOfShaderIf.begin(); it != m_vecOfShaderIf.end(); ++it)
	{
		if (!(*it)->getName().compare(arg0))
		{
			std::cout << "- FOUND -" << (*it)->getName() << " number of shared objects " << (*it).use_count() << std::endl;
			return *it;
		}
	}

	// If can't find element in vector, return first
	return m_vecOfShaderIf[0];
}

std::shared_ptr<Loader::LoaderIf>& Common::Factory::getLoaderIf(const std::string& arg0)
{
	for (auto it = m_vecOfLoaderIf.begin(); it != m_vecOfLoaderIf.end(); ++it)
	{
		if (!(*it)->getName().compare(arg0))
		{
			std::cout << "- FOUND -" << (*it)->getName() << " number of shared objects " << (*it).use_count() << std::endl;
			return *it;
		}
	}

	// If can't find element in vector, return first
	return m_vecOfLoaderIf[0];
}

std::shared_ptr<GPUObject::GPUObjectIf>& Common::Factory::getGPUObjectIf(const std::string& arg0)
{
	for (auto it = m_vecOfGPUObjectIf.begin(); it != m_vecOfGPUObjectIf.end(); ++it)
	{
		if (!(*it)->getName().compare(arg0))
		{
			std::cout << "- FOUND -" << (*it)->getName() << " number of shared objects " << (*it).use_count() << std::endl;
			return *it;
		}
	}

	// If can't find element in vector, return first
	return m_vecOfGPUObjectIf[0];
}