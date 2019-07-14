#include "staticModel.h"

#include "factory.h"

Model::StaticModel::StaticModel(const std::string& name) : 
	m_name(name), 
	m_modelPosition(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_modelScale(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_modelRotateAround(glm::vec3(0.0f, 0.0f, 0.0f)),
    m_angle(0.0f),
	m_modelMatrix(glm::mat4(0.0f))
{
	FACTORY.getLog()->LOGFILE(LOG "StaticModel " + m_name + " created!");
}


Model::StaticModel::~StaticModel()
{
}


void Model::StaticModel::preInit()
{
	FACTORY.getLog()->LOGFILE(LOG "StaticModel " + m_name + " preInit method called!");


	// MODEL VARIABLES - TODO: get this init model values from DB
    // 1] Update model position
	m_modelPosition = glm::vec3(385.0f, 0.0f, 375.0f);
	m_modelMatrix = glm::translate(glm::mat4(1.0f), m_modelPosition);

	// 2] Update model rotation around axes
	m_angle = -1.57f;
	m_modelRotateAround = glm::vec3(1.0f, 0.0f, 0.0f);
	m_modelMatrix = glm::rotate(m_modelMatrix, m_angle, m_modelRotateAround);

	// 3] Update model with scale factor
	m_modelScale = glm::vec3(10.0f, 10.0f, 10.0f);
	m_modelMatrix = glm::scale(m_modelMatrix, m_modelScale);
}


void Model::StaticModel::postInit()
{
	FACTORY.getLog()->LOGFILE(LOG "StaticModel " + m_name + " postInit method called!");

	// 1] Get GPUObject instance name from DB for this instance
	std::string gpuObjectString;
	FACTORY.getDatabase()->getStringFromDB(m_name, "GPUObject", gpuObjectString);

	// 2] Get gpuObject instance from Factory
	m_gpuObjectIf = Common::Factory::getInstance().getGPUObjectIf(gpuObjectString);

	// 3] Set model VAO
	m_VAO = m_gpuObjectIf->getVAO();

	// 4] Get vector (column) of Mesh instances names from DB
	std::vector<std::string> vecOfStringMeshesNames;
	FACTORY.getDatabase()->get(m_name, "mesh", vecOfStringMeshesNames);

	// 5] Set meshIf pointers in vector of mesh interfaces
	for (auto it1 = vecOfStringMeshesNames.begin(); it1 < vecOfStringMeshesNames.end(); ++it1)
	{
		std::shared_ptr<Mesh::MeshIf>& m_meshIf = FACTORY.getMeshIf(*it1);
		m_vecOfdefaultMeshIf.push_back(m_meshIf);
	}
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

	auto itt = m_gpuObjectIf->getMeshVec().begin();
	for (auto it = m_vecOfdefaultMeshIf.begin(); it != m_vecOfdefaultMeshIf.end(); ++it)
	{
		// RENDER EACH MESH IN MODEL
		(*it)->render(m_modelMatrix, itt->m_VBO, itt->m_IBO, itt->m_NumOfInds);
		++itt;
	}
};


void Model::StaticModel::cmdPrompt(const std::string& arg0)
{
	std::cout << "StaticModel: " << m_name << std::endl;
	std::cout << " Model < model name > { info | set | get | help } " << std::endl;
}
