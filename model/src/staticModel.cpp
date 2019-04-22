#include "staticModel.h"

#include "error.h"
#include "factory.h"

Model::StaticModel::StaticModel(Common::Error& err, const std::string& name) : m_name(name)
{
	std::cout << "StaticModel created!" << std::endl;

	std::cout << " // STATIC MODEL // show me gpuObjectsIf " << '\n';
	// Common::Factory::getInstance().showMeObjects("GPUObjectIf");

	// std::shared_ptr<GPUObject::GPUObjectIf> tempGPUObj = Common::Factory::getInstance().getGPUObjectIf("vanquishGPUObject");
	// tempGPUObj->info();
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

	// Combine meshes (VBO, IBO)
	

}


void Model::StaticModel::setGPUObject(const std::shared_ptr<GPUObject::GPUObjectIf>& gpuObjectIf)
{
	std::cout << " >>> [Model::StaticModel::setGPUObject] ..." << std::endl;

	m_gpuObjectIf = gpuObjectIf;
	m_gpuObjectIf->info();

	m_VAO = m_gpuObjectIf->getVAO();
}


void Model::StaticModel::setMesh(const std::shared_ptr<Mesh::MeshIf>& meshIf)
{
	std::cout << "[Model::StaticModel::setMesh] ..." << std::endl;

	m_vecOfdefaultMeshIf.push_back(meshIf);
}


// 1 ] Bind VAO glBindVertexArray(VAO); 
// 2 ] Set Pointers    (glVertexAttribPointer); 
// 3 ] Enable Pointers (glEnableVertexAttribArray); 
// For each mesh:
	// 4.1 ] glBindBuffer(GL_ARRAY_BUFFER)
	// 4.2 ] glBindBuffer(GL_ELEMENT_ARRAY_BUFFER)
	// 4.3 ] Active shader glUseProgram(ShaderID);
	// 4.4 ] Update Uniform(s)

	// 4.5 ] Active Textures
	// 4.6 ] Bind Textures
	// 4.7 ] Render mesh (model) (glDrawElements ili another method)
// 5 ] Disable everything
void Model::StaticModel::render() 
{
    std::cout << "Model::StaticModel::render()" << std::endl;
	std::cout << " VAO: " << m_VAO << std::endl;

	glBindVertexArray(m_VAO);

	for (auto it = m_vecOfdefaultMeshIf.begin(); it != m_vecOfdefaultMeshIf.end(); ++it)
	{
		// glBindBuffer(GL_ARRAY_BUFFER, _staticModel.getVectorOfMeshes()[i].VBO);
		// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _staticModel.getVectorOfMeshes()[i].IBO);

		// GET SHADER FOR EACH MESH IN MODEL
		(*it)->render();
	}
};


void Model::StaticModel::cmdPrompt(const std::string& arg0)
{
	std::cout << "StaticModel: " << m_name << std::endl;
	std::cout << " Model < model name > { info | set | get | help } " << std::endl;

	// defaultMeshIf0 = Common::Factory::getInstance().getMeshIf("smartMesh_0");
	// render();
}
