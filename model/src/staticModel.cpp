#include "staticModel.h"

#include "factory.h"


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
	FACTORY.getLog()->LOGFILE(LOG "StaticModel: " + m_name + " created. [CONSTRUCTOR]");
	FACTORY.getLog()->LOGFILE(LOG "StaticModel: " + m_name + " dbPath: " + m_dbPathWithName);
}


Model::StaticModel::~StaticModel()
{
}


void Model::StaticModel::preInitialization()
{
	FACTORY.getLog()->LOGFILE(LOG " ---- preInit start ---- ");
	// 1] Update model position
	std::string dBKey = m_dbPathWithName + "position";
	FACTORY.getDatabase()->getVec3(dBKey, m_modelPosition);
	FACTORY.getLog()->LOGFILE(LOG "StaticModel: " + m_name + " m_modelPosition: " + std::to_string(m_modelPosition.x) + " " + std::to_string(m_modelPosition.y) + " " + std::to_string(m_modelPosition.z));
	m_modelMatrix = glm::translate(glm::mat4(1.0f), m_modelPosition);
	
	// 2] Update model rotation around axes
	dBKey = m_dbPathWithName + "rotation";
	FACTORY.getDatabase()->getFloat(dBKey, m_angle);
	FACTORY.getLog()->LOGFILE(LOG "StaticModel: " + m_name + " m_angle: " + std::to_string(m_angle));
	dBKey = m_dbPathWithName + "rotateAround";
	FACTORY.getDatabase()->getVec3(dBKey, m_modelRotateAround);
	FACTORY.getLog()->LOGFILE(LOG "StaticModel: " + m_name + " m_modelRotateAround: " + std::to_string(m_modelRotateAround.x) + " " + std::to_string(m_modelRotateAround.y) + " " + std::to_string(m_modelRotateAround.z));
	m_modelMatrix = glm::rotate(m_modelMatrix, m_angle, m_modelRotateAround);

	// 3] Update model with scale factor
	dBKey = m_dbPathWithName + "modelScale";
	FACTORY.getDatabase()->getVec3(dBKey, m_modelScale);
	FACTORY.getLog()->LOGFILE(LOG "StaticModel: " + m_name + " m_modelScale: " + std::to_string(m_modelScale.x) + " " + std::to_string(m_modelScale.y) + " " + std::to_string(m_modelScale.z));
	m_modelMatrix = glm::scale(m_modelMatrix, m_modelScale);

	FACTORY.getLog()->LOGFILE(LOG " ---- preInit end ---- ");
}


void Model::StaticModel::postInitialization()
{
	FACTORY.getLog()->LOGFILE(LOG " ---- postInit start ---- ");
	// 1] Get Camera
	std::string dBKey = m_dbPathWithName + "camera";
	std::vector<std::string> cameraString;
	FACTORY.getDatabase()->getStringsFromDB(dBKey, cameraString);
	FACTORY.getLog()->LOGFILE(LOG "StaticModel: " + m_name + " cameraString: " + cameraString[0]);
	m_cameraIf = Common::Factory::getInstance().getCameraIf(cameraString[0]);

	// 2] Get Light
	dBKey = m_dbPathWithName + "light";
	std::vector<std::string> lightString;
	FACTORY.getDatabase()->getStringsFromDB(dBKey, lightString);
	FACTORY.getLog()->LOGFILE(LOG "StaticModel: " + m_name + " lightString: " + lightString[0]);
	m_lightIf = Common::Factory::getInstance().getLightIf(lightString[0]);

	// 3] Get GPUObjectModel
	dBKey = m_dbPathWithName + "gpuObjectModel";
	std::vector<std::string> gpuObjectModelString;
	FACTORY.getDatabase()->getStringsFromDB(dBKey, gpuObjectModelString);
	FACTORY.getLog()->LOGFILE(LOG "StaticModel: " + m_name + " gpuObjectModelString: " + gpuObjectModelString[0]);
	m_gpuObjectIf = Common::Factory::getInstance().getGPUObjectIf(gpuObjectModelString[0]);

	// 4] Get TextureObject
	dBKey = m_dbPathWithName + "textureObjectModel";
	std::vector<std::string> textureObjectModelString;
	FACTORY.getDatabase()->getStringsFromDB(dBKey, textureObjectModelString);
	FACTORY.getLog()->LOGFILE(LOG "StaticModel: " + m_name + " textureObjectModelString: " + textureObjectModelString[0]);
	m_gpuObjectTextureIf = Common::Factory::getInstance().getGPUObjectIf(textureObjectModelString[0]);

	// 5] Get Shaders
	dBKey = m_dbPathWithName + "shaders";
	std::vector<std::string> shadersString;
	FACTORY.getDatabase()->getStringsFromDB(dBKey, shadersString);
	
	for (auto s : shadersString)
	{	
		FACTORY.getLog()->LOGFILE(LOG "StaticModel: " + m_name + " shader: " + s);
	    std::shared_ptr<Shader::ShaderIf>& m_meshIf = FACTORY.getShaderIf(s);
		m_vecOfdefaultShaderIf.push_back(m_meshIf);		
	}

	FACTORY.getLog()->LOGFILE(LOG "Num of Meshes  : " + std::to_string(m_gpuObjectIf->getMeshVec().size()));
	FACTORY.getLog()->LOGFILE(LOG "Num of Textures: " + std::to_string(m_gpuObjectTextureIf->getTextureStructVec().size()));
	FACTORY.getLog()->LOGFILE(LOG "Num of Shaders : " + std::to_string(shadersString.size()));

	FACTORY.getLog()->LOGFILE(LOG " ---- postInit end ---- ");
}


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
	std::cout << " +------------+" << '\n';
	std::cout << " | MODEL INFO |" << '\n';
	std::cout << " +------------+" << '\n';
	std::cout << "| Model Name............: " << m_name << '\n';
	std::cout << "| Model VAO.............: " << m_VAO << '\n';
	std::cout << "|  Model Position.......: " << m_modelPosition[0] << " " << m_modelPosition[1] << " " << m_modelPosition[2] << '\n';
	std::cout << "|  Model Scale..........: " << m_modelScale[0] << " " << m_modelScale[1] << " " << m_modelScale[2] << '\n';
	std::cout << "|  Model Rotate Around..: " << m_modelRotateAround[0] << " " << m_modelRotateAround[1] << " " << m_modelRotateAround[2] << '\n';
	std::cout << "|  Model Angle..........: " << m_angle << '\n';
	std::cout << " +-------------+" << '\n';
	std::cout << " | CAMERA INFO |" << '\n';
	std::cout << " +-------------+" << '\n';
	m_cameraIf->dump();
	std::cout << " +------------+" << '\n';
	std::cout << " | LIGHT INFO |" << '\n';
	std::cout << " +------------+" << '\n';
	m_lightIf->dump();

	auto it0 = m_gpuObjectIf->getMeshVec().begin();
	auto it1 = m_gpuObjectTextureIf->getTextureStructVec().begin();

	std::cout << " +--------------------+" << '\n';
	std::cout << " | MESH MATERIAL INFO |" << '\n';
	std::cout << " +--------------------+" << '\n';
	for (auto it = m_vecOfdefaultShaderIf.begin(); it != m_vecOfdefaultShaderIf.end(); ++it)
	{
		std::cout << "| < " << it1->m_name << " >" << '\n';
		(*it0).dump(); 
		std::cout << "| " << '\n';
		(*it1).dump();
		std::cout << "|" << '\n';
		std::cout << "|| Shader: " << (*it)->getName() << '\n';
		std::cout << " +-------------------- " << '\n';

		++it0;
		++it1;
	}
}


void Model::StaticModel::cmdPrompt(const std::string& arg0)
{
	int ONE = 1;
	int TWO = 2;
	int THREE = 3;
	// -- FIRST DEFINE arg0 --
	std::istringstream stringOfElements(arg0);
	std::vector<std::string> vectorOfLocalStrings((std::istream_iterator<std::string>(stringOfElements)), std::istream_iterator<std::string>());

	std::string regexPattern;
	if (vectorOfLocalStrings.size() == TWO)
	{
		regexPattern = "models\\s+" + m_name;
	}
	else if (vectorOfLocalStrings.size() == THREE)
	{
		regexPattern = "models\\s+" + m_name + "\\s+(\\w+)";
	}
	// ----

	std::smatch match;
	std::regex _regex(regexPattern);
	if (std::regex_search(arg0, match, _regex))
	{
		if (vectorOfLocalStrings.size() == TWO)
		{
			std::cout << " models " << m_name << " <set | dump>" << std::endl;
		}
		else if (vectorOfLocalStrings.size() == THREE)
		{
			if (!match.str(1).compare("dump"))
			{
				dump();
			}
		}		
	}
}
