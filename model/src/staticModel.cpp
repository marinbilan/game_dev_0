#include "staticModel.h"
#include "error.h"


Model::StaticModel::StaticModel(Common::Error& err, const std::string& name) : m_name(name)
{
	std::cout << "StaticModel created!" << std::endl;
}


Model::StaticModel::~StaticModel()
{
	std::cout << "StaticModel destructor called!" << std::endl;
}


void Model::StaticModel::preInit()
{

}


void Model::StaticModel::postInit()
{
	std::cout << "postInit function called!" << std::endl;
}


void Model::StaticModel::cmdPrompt(const std::string& arg0)
{
	std::cout << "cmdPrompt object: " << m_name << " called with arg: " << arg0 << std::endl;
}
