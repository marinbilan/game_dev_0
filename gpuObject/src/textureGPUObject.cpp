#include "textureGPUObject.h"

#include "factory.h"


GPUObject::TextureGPUObject::TextureGPUObject(const std::string& name) : m_name(name)
{
	FACTORY.getLog()->LOGFILE(LOG "TextureGPUObject: " + m_name + " created.");
}


GPUObject::TextureGPUObject::~TextureGPUObject()
{
}


const std::string& GPUObject::TextureGPUObject::getName()
{
	return m_name;
}


void GPUObject::TextureGPUObject::preInitialization()
{
}


void GPUObject::TextureGPUObject::postInitialization()
{
}


void GPUObject::TextureGPUObject::setTextureStructInVec(const TextureStructure& textureStruct)
{
	m_vecOfTextures.push_back(textureStruct);
}


std::vector<GPUObject::TextureStructure>& GPUObject::TextureGPUObject::getTextureStructVec()
{
	return m_vecOfTextures;
}

void GPUObject::TextureGPUObject::info()
{
	std::cout << " GPUObject Name: " << m_name << '\n';
	for (auto texture : m_vecOfTextures)
	{
		texture.dump();
	}
}