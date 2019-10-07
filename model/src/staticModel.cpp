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


Model::StaticModel::StaticModel(const std::string& dbPath, const std::string& name) :
	m_dbPath(dbPath),
	m_name(name),
	m_modelPosition(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_modelScale(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_modelRotateAround(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_angle(0.0f),
	m_modelMatrix(glm::mat4(0.0f))
{
	m_dbPathWithName = m_dbPath + m_name + "_";
	// FACTORY.getLog()->LOGFILE(LOG "StaticModel " + m_name + " created!");
	std::cout << " CREATION INSTANCE - m_dbPathWithName: " << m_dbPathWithName << " modelName: " << m_name << '\n';
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

	std::string gpuObjectString;
	FACTORY.getDatabase()->getStringFromDB(m_name, "GPUObjectModel", gpuObjectString);

	std::string gpuObjectTextureString;
	FACTORY.getDatabase()->getStringFromDB(m_name, "GPUObjectTexture", gpuObjectTextureString);

	std::string cameraString;
	FACTORY.getDatabase()->getRest(m_name, "camera", cameraString);

	std::string lightString;
	FACTORY.getDatabase()->getRest(m_name, "light", lightString);

	// 1] Get gpuObject instance from Factory
	m_gpuObjectIf = Common::Factory::getInstance().getGPUObjectIf(gpuObjectString);
	m_gpuObjectTextureIf = Common::Factory::getInstance().getGPUObjectIf(gpuObjectTextureString);

	m_cameraIf = Common::Factory::getInstance().getCameraIf(cameraString);
	m_lightIf = Common::Factory::getInstance().getLightIf(lightString);

	// 2] Get vector (column) of Shader instances names from DB
	std::vector<std::string> vecOfStringShaderNames;
	FACTORY.getDatabase()->get(m_name, "shader", vecOfStringShaderNames);

	// 3] Set shaderIf pointers in vector of shader interfaces
	for (auto it = vecOfStringShaderNames.begin(); it < vecOfStringShaderNames.end(); ++it)
	{
		std::shared_ptr<Shader::ShaderIf>& m_meshIf = FACTORY.getShaderIf(*it);
		m_vecOfdefaultShaderIf.push_back(m_meshIf);
	}
}


// ========================================================================================
// NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION
// ========================================================================================
void Model::StaticModel::preInitialization()
{
	// 1] Update model position
	std::string dBKey = m_dbPathWithName + "position";
	FACTORY.getDatabase()->getVec3(dBKey, m_modelPosition);
	m_modelMatrix = glm::translate(glm::mat4(1.0f), m_modelPosition);
	
	// 2] Update model rotation around axes
	// ...

	// 3] Update model with scale factor
	// ...
}


void Model::StaticModel::postInitialization()
{
	// std::cout << " POSTITIALIZATION " << '\n';
}

// 1 ] Bind VAO        (glBindVertexArray (VAO)); 
// 2 ] Bind VBO        (glBindBuffer (VBO)); 
// 3 ] Bind IBO        (glBindBuffer (IBO)); 

// 4 ] Set Pointers    (glVertexAttribPointer); 

// 5 ] Enable Pointers (glEnableVertexAttribArray); 

// 6 ] Active shader glUseProgram(ShaderID);
// For each mesh:
	// 4.4 ] Update Uniform(s)

	// 4.5 ] Active Textures
	// 4.6 ] Bind Textures
	// 4.7 ] Render mesh (model) (glDrawElements ili another method)
// 5 ] Disable everything
void Model::StaticModel::render() 
{
	auto it0 = m_gpuObjectIf->getMeshVec().begin();
	auto it1 = m_gpuObjectTextureIf->getTextureStructVec().begin();

	for (auto it = m_vecOfdefaultShaderIf.begin(); it != m_vecOfdefaultShaderIf.end(); ++it)
	{
		// RENDER EACH MESH IN MODEL
		(*it)->render(m_modelMatrix, *it0, *it1, m_cameraIf, m_lightIf);

		++it0;
		++it1;
	}
};


void Model::StaticModel::cmdPrompt(const std::string& arg0)
{
	std::cout << "StaticModel: " << m_name << std::endl;
	// std::cout << " Model < model name > { info | set | get | help } " << std::endl;

	std::cout << "m_gpuObjectIf name: " << m_gpuObjectIf->getName() << std::endl;
	// std::cout << "VAO: " << m_VAO << std::endl;
	m_gpuObjectIf->info();


}
