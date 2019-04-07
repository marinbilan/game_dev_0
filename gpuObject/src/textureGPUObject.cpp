#include "textureGPUObject.h"

#include "error.h"


GPUObject::TextureGPUObject::TextureGPUObject(Common::Error& err, const std::string& name) : m_name(name)
{
	std::cout << "TextureGPUObject created!" << std::endl;
}


GPUObject::TextureGPUObject::~TextureGPUObject()
{
	std::cout << "TextureGPUObject destructor called!" << std::endl;
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
	std::cout << "postInit function called!" << std::endl;
}

