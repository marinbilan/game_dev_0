#include "staticModel.h"

#include "factory.h"

Model::StaticModel::StaticModel(Common::Error& err, const std::string& name) : m_name(name)
{
	std::cout << "StaticModel created!" << std::endl;

	std::cout << " // STATIC MODEL // show me gpuObjectsIf " << '\n';
	// Common::Factory::getInstance().showMeObjects("GPUObjectIf");

	// std::shared_ptr<GPUObject::GPUObjectIf> tempGPUObj = Common::Factory::getInstance().getGPUObjectIf("vanquishGPUObject");
	// tempGPUObj->info();

	// MODEL VARIABLES - TODO: move this in DB
	modelMatrix = glm::mat4(1.0f);

	modelPosition = glm::vec3(385.0f, 0.0f, 375.0f);
	modelMatrix = glm::translate(glm::mat4(1.0f), modelPosition);

	angle = -1.57f;
	modelRotateAround = glm::vec3(1.0f, 0.0f, 0.0f);
	modelMatrix = glm::rotate(modelMatrix, angle, modelRotateAround);

	modelScale = glm::vec3(10.0f, 10.0f, 10.0f);
	modelMatrix = glm::scale(modelMatrix, modelScale);
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


void Model::StaticModel::connect()
{
	std::cout << " >>> [Model::StaticModel::connect] ..." << std::endl;
	std::cout << " >>> m_gpuObjectIf->getVecOfVBOs().size() = " << m_gpuObjectIf->getVecOfVBOs().size() << '\n';
	std::cout << " >>> m_vecOfdefaultMeshIf.size() = " << m_vecOfdefaultMeshIf.size() << '\n';

	std::vector<std::shared_ptr<Mesh::MeshIf>>::iterator it = m_vecOfdefaultMeshIf.begin();

	GLuint temp;
	for (int i = 0; i < m_gpuObjectIf->getVecOfVBOs().size(); ++i)
	{
		(*it)->setVBO(m_gpuObjectIf->getVecOfVBOs()[i]);
		(*it)->setIBO(m_gpuObjectIf->getVecOfIBOs()[i]);
		(*it)->setNumOfInd(m_gpuObjectIf->getVecOfNumOfInds()[i]);

		++it;
	}
	
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
	glBindVertexArray(m_VAO);

	for (auto it = m_vecOfdefaultMeshIf.begin(); it != m_vecOfdefaultMeshIf.end(); ++it)
	{
		// GET SHADER FOR EACH MESH IN MODEL
		(*it)->render(modelMatrix);
	}
};


void Model::StaticModel::cmdPrompt(const std::string& arg0)
{
	std::cout << "StaticModel: " << m_name << std::endl;
	std::cout << " Model < model name > { info | set | get | help } " << std::endl;

	// defaultMeshIf0 = Common::Factory::getInstance().getMeshIf("smartMesh_0");
	// render();
}
