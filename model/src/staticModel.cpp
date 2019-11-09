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

	std::string instName = m_dbPathWithName + m_name;
	FACTORY.getLog()->LOGFILE(LOG "StaticModel: " + m_name + " created.");
}


Model::StaticModel::~StaticModel()
{
}


void Model::StaticModel::preInitialization()
{
	// 1] Update model position
	std::string dBKey = m_dbPathWithName + "position";
	FACTORY.getDatabase()->getVec3(dBKey, m_modelPosition);
	m_modelMatrix = glm::translate(glm::mat4(1.0f), m_modelPosition);
	
	// 2] Update model rotation around axes
	dBKey = m_dbPathWithName + "rotation";
	FACTORY.getDatabase()->getFloat(dBKey, m_angle);
	dBKey = m_dbPathWithName + "rotateAround";
	FACTORY.getDatabase()->getVec3(dBKey, m_modelRotateAround);
	m_modelMatrix = glm::rotate(m_modelMatrix, m_angle, m_modelRotateAround);

	// 3] Update model with scale factor
	dBKey = m_dbPathWithName + "modelScale";
	FACTORY.getDatabase()->getVec3(dBKey, m_modelScale);
	m_modelMatrix = glm::scale(m_modelMatrix, m_modelScale);
}


void Model::StaticModel::postInitialization()
{
	// 1] Get Camera
	std::string dBKey = m_dbPathWithName + "camera";
	std::vector<std::string> cameraString;
	FACTORY.getDatabase()->getStringsFromDB(dBKey, cameraString);
	m_cameraIf = Common::Factory::getInstance().getCameraIf(cameraString[0]);

	// 2] Get Light
	dBKey = m_dbPathWithName + "light";
	std::vector<std::string> lightString;
	FACTORY.getDatabase()->getStringsFromDB(dBKey, lightString);
	m_lightIf = Common::Factory::getInstance().getLightIf(lightString[0]);

	// 3] Get GPUObjectModel
	dBKey = m_dbPathWithName + "gpuObjectModel";
	std::vector<std::string> gpuObjectModelString;
	FACTORY.getDatabase()->getStringsFromDB(dBKey, gpuObjectModelString);
	m_gpuObjectIf = Common::Factory::getInstance().getGPUObjectIf(gpuObjectModelString[0]);

	// 4] Get TextureObject
	dBKey = m_dbPathWithName + "textureObjectModel";
	std::vector<std::string> textureObjectModelString;
	FACTORY.getDatabase()->getStringsFromDB(dBKey, textureObjectModelString);
	m_gpuObjectTextureIf = Common::Factory::getInstance().getGPUObjectIf(textureObjectModelString[0]);

	// 5] Get Shaders
	dBKey = m_dbPathWithName + "shaders";
	std::vector<std::string> shadersString;
	FACTORY.getDatabase()->getStringsFromDB(dBKey, shadersString);
	
	for (auto s : shadersString)
	{
		
	    std::shared_ptr<Shader::ShaderIf>& m_meshIf = FACTORY.getShaderIf(s);
		m_vecOfdefaultShaderIf.push_back(m_meshIf);
		
	}

	// TODO: remove
	dump();
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


void Model::StaticModel::dump()
{
	std::cout << "| ---- | MODEL INFO | ---- " << std::endl;
	std::cout << "| Model Name:           " << m_name << std::endl;
	std::cout << "| Model VAO:            " << m_VAO << std::endl;
	std::cout << "|  Model Position:      " << m_modelPosition[0] << " " << m_modelPosition[1] << " " << m_modelPosition[2] << '\n';
	std::cout << "|  Model Scale:         " << m_modelScale[0] << " " << m_modelScale[1] << " " << m_modelScale[2] << '\n';
	std::cout << "|  Model Rotate Around: " << m_modelRotateAround[0] << " " << m_modelRotateAround[1] << " " << m_modelRotateAround[2] << '\n';
	std::cout << "|  Model Angle:         " << m_angle << '\n';
	std::cout << "|- " << '\n';
	std::cout << "| ---- | CAMERA INFO | ---- " << '\n';
	m_cameraIf->dump();
	std::cout << "|- " << '\n';
	std::cout << "| ---- | LIGHT INFO | ---- " << '\n';
	m_lightIf->dump();

	auto it0 = m_gpuObjectIf->getMeshVec().begin();
	auto it1 = m_gpuObjectTextureIf->getTextureStructVec().begin();

	std::cout << "| ---- | MESH MATERIAL INFO | ---- " << '\n';
	for (auto it = m_vecOfdefaultShaderIf.begin(); it != m_vecOfdefaultShaderIf.end(); ++it)
	{
		std::cout << "| ---- < " << it1->m_name << " > ---- " << '\n';
		(*it0).dump(); 
		std::cout << "|- " << '\n';
		(*it1).dump();
		std::cout << "|- " << '\n';
		std::cout << "|| Shader: " << (*it)->getName() << '\n';

		++it0;
		++it1;
	}
}


void Model::StaticModel::cmdPrompt(const std::string& arg0)
{
	std::cout << "StaticModel: " << m_name << std::endl;
	// std::cout << " Model < model name > { info | set | get | help } " << std::endl;

	std::cout << "m_gpuObjectIf name: " << m_gpuObjectIf->getName() << std::endl;
	// std::cout << "VAO: " << m_VAO << std::endl;
	// m_gpuObjectIf->info();
}
