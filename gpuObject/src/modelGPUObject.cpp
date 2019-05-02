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


void GPUObject::ModelGPUObject::setVAO(GLuint VAO)
{
	m_VAO = VAO;
}


GLuint GPUObject::ModelGPUObject::getVAO()
{
	return m_VAO;
}


void GPUObject::ModelGPUObject::setVBO(GLuint VBO)
{
	m_vecOfVBOs.push_back(VBO);
}


void GPUObject::ModelGPUObject::setIBO(GLuint IBO)
{
	m_vecOfIBOs.push_back(IBO);
}


void GPUObject::ModelGPUObject::setNumOfInd(GLuint numOfInd)
{
	m_vecOfNumOfInds.push_back(numOfInd);
}


std::vector<GLuint>& GPUObject::ModelGPUObject::getVecOfVBOs()
{
	return m_vecOfVBOs;
}


std::vector<GLuint>& GPUObject::ModelGPUObject::getVecOfIBOs()
{
	return m_vecOfIBOs;
}


std::vector<GLuint>& GPUObject::ModelGPUObject::getVecOfNumOfInds()
{
	return m_vecOfNumOfInds;
}


void GPUObject::ModelGPUObject::info()
{
	std::cout << " _ info m_VAO: " << m_VAO << '\n';
	for (auto it = m_vecOfVBOs.begin(); it != m_vecOfVBOs.end(); ++it)
	{
		std::cout << " ___ info m_VBO: " << *it << '\n';
	}
	
	for (auto it = m_vecOfIBOs.begin(); it != m_vecOfIBOs.end(); ++it)
	{
		std::cout << " ___ info m_IBO: " << *it << '\n';
	}
	
}

