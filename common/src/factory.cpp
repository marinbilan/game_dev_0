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


// GET
std::shared_ptr<Loader::LoaderIf>& Common::Factory::getLoaderIf(const std::string& arg0)
{
	return getObjectFromVec(m_vecOfLoaderIf, arg0);
}

std::shared_ptr<GPUObject::GPUObjectIf>& Common::Factory::getGPUObjectIf(const std::string& arg0)
{
	return getObjectFromVec(m_vecOfGPUObjectIf, arg0);
}

std::shared_ptr<Model::ModelIf>& Common::Factory::getModelIf(const std::string& arg0)
{
	return getObjectFromVec(m_vecOfModelIf, arg0);
}

std::shared_ptr<Mesh::MeshIf>& Common::Factory::getMeshIf(const std::string& arg0)
{
	return getObjectFromVec(m_vecOfMeshIf, arg0);
}

std::shared_ptr<Shader::ShaderIf>& Common::Factory::getShaderIf(const std::string& arg0)
{
	return getObjectFromVec(m_vecOfShaderIf, arg0);
}
