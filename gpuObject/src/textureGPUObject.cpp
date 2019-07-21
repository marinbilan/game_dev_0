#include "textureGPUObject.h"


GPUObject::TextureGPUObject::TextureGPUObject(const std::string& name) : m_name(name)
{
	std::cout << "GPUObject::TextureGPUObject::TextureGPUObject() constructor called!" << '\n';
}


GPUObject::TextureGPUObject::~TextureGPUObject()
{
	std::cout << "GPUObject::TextureGPUObject::~TextureGPUObject() destructor called!" << '\n';
}


const std::string& GPUObject::TextureGPUObject::getName()
{
	return m_name;
}


void GPUObject::TextureGPUObject::preInit()
{

}


void GPUObject::TextureGPUObject::postInit()
{
	std::cout << "GPUObject::TextureGPUObject::postInit() destructor called!" << '\n';
}


void GPUObject::TextureGPUObject::setTextureStructInVec(const TextureStructure& textureStruct)
{
	m_vecOfTextures.push_back(textureStruct);
	std::cout << " sizeeeeeeeeeeeeeeeeeeee: " << m_vecOfTextures.size() << '\n';
}


std::vector<GPUObject::TextureStructure>& GPUObject::TextureGPUObject::getTextureStructVec()
{
	return m_vecOfTextures;
}


void GPUObject::TextureGPUObject::setTextureID(GLuint textureID)
{
	m_textureID = textureID;
}


GLuint GPUObject::TextureGPUObject::getTextureID()
{
	return m_textureID;
}