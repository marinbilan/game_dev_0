#include "modelGPUObject.h"

#include "error.h"


GPUObject::ModelGPUObject::ModelGPUObject(Common::Error& err, const std::string& name) : m_name(name)
{
	std::cout << "ModelGPUObject created!" << std::endl;
}


GPUObject::ModelGPUObject::~ModelGPUObject()
{
	std::cout << "ModelGPUObject destructor called!" << std::endl;
}


const std::string& GPUObject::ModelGPUObject::getName()
{
	return m_name;
}


void GPUObject::ModelGPUObject::preInit()
{

}


void GPUObject::ModelGPUObject::postInit()
{
	std::cout << "postInit function called!" << std::endl;
}

