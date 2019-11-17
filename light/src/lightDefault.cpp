#include "lightDefault.h"
#include "factory.h"


Light::LightDefault::LightDefault(const std::string& dbPath, const std::string& name) :
	m_dbPath(dbPath),
	m_name(name)
{
	m_dbPathWithName = m_dbPath + m_name + "_";

	std::string instName = m_dbPathWithName + m_name;
	FACTORY.getLog()->LOGFILE(LOG "StaticModel: " + m_name + " created.");
}


Light::LightDefault::~LightDefault()
{
}


void Light::LightDefault::preInitialization()
{
	// 1] Get Light Position
	std::string dBKey = m_dbPathWithName + "lightPosition";
	FACTORY.getDatabase()->getVec3(dBKey, m_lightPosition);

	// 2] Get Light Color
	dBKey = m_dbPathWithName + "lightColor";
	FACTORY.getDatabase()->getVec3(dBKey, m_lightColors);
}


void Light::LightDefault::postInitialization()
{
}


glm::vec3& Light::LightDefault::getLightPosition()
{
	return m_lightPosition;
}


glm::vec3& Light::LightDefault::getLightColors()
{
	return m_lightColors;
}


void Light::LightDefault::dump()
{
	std::cout << "| Light Name:      " << m_name << std::endl;
	std::cout << "|  Light Position: " << m_lightPosition[0] << " " << m_lightPosition[1] << " " << m_lightPosition[2] << '\n';
	std::cout << "|  Light Colors:    " << m_lightColors[0] << " " << m_lightColors[1] << " " << m_lightColors[2] << '\n';
};


void Light::LightDefault::cmdPrompt(const std::string& arg0)
{

}