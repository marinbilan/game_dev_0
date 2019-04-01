#include "staticModel.h"

#include "error.h"
#include "factory.h"

Model::StaticModel::StaticModel(Common::Error& err, const std::string& name) : m_name(name)
{
	std::cout << "StaticModel created!" << std::endl;
}


Model::StaticModel::~StaticModel()
{
	std::cout << "StaticModel destructor called!" << std::endl;
}


void Model::StaticModel::render() 
{
    std::cout << "Model::StaticModel::render()" << std::endl;
    defaultMeshIf0->render();
};


void Model::StaticModel::preInit()
{
    
}


void Model::StaticModel::postInit()
{
	std::cout << "postInit function called!" << std::endl;
	

}


void Model::StaticModel::cmdPrompt(const std::string& arg0)
{
	std::cout << "StaticModel: " << m_name << std::endl;
	std::cout << " Model < model name > { info | set | get | help } " << std::endl;

	defaultMeshIf0 = Common::Factory::getInstance().getMeshIf("smartMesh_0");
	render();
}
