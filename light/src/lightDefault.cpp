#include "lightDefault.h"
#include "factory.h"

Light::LightDefault::LightDefault(const std::string& name) : m_name(name)
{
	preInit();
}


Light::LightDefault::LightDefault(const std::string& dbPath, const std::string& name) :
	m_dbPath(dbPath),
	m_name(name)
{
	preInit(); // TODO: remove this
	m_dbPathWithName = m_dbPath + m_name + "_";
	std::cout << " CREATION INSTANCE - m_dbPathWithName: " << m_dbPathWithName << " modelName: " << m_name << '\n';
}


Light::LightDefault::~LightDefault()
{
}


void Light::LightDefault::preInit()
{
	FACTORY.getLog()->LOGFILE(LOG "LightDefault " + m_name + " created!");

	FACTORY.getDatabase()->getVec3_21(m_name, "lightPosition", m_lightPosition);
	FACTORY.getDatabase()->getVec3_21(m_name, "lightColor", m_lightColors);
}


void Light::LightDefault::postInit()
{
}


// ========================================================================================
// NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION
// ========================================================================================
void Light::LightDefault::preInitialization()
{
	// std::cout << " preInitialization - m_dbPathWithName: " << m_dbPathWithName << " modelName: " << m_name << '\n';
	// GET light position and light color from DB

	// 1] Get Light Position
	std::string dBKey = m_dbPathWithName + "lightPosition";
	FACTORY.getDatabase()->getVec3(dBKey, m_lightPosition);
	std::cout << " xxxx Loght Position : " << m_lightPosition[0] << m_lightPosition[1] << m_lightPosition[2] << '\n';

	// 2] Get Light Color
	dBKey = m_dbPathWithName + "lightColor";
	FACTORY.getDatabase()->getVec3(dBKey, m_lightColors);
	std::cout << " xxxx Loght Position : " << m_lightColors[0] << m_lightColors[1] << m_lightColors[2] << '\n';
}


void Light::LightDefault::postInitialization()
{
	std::cout << " postInitialization - m_dbPathWithName: " << m_dbPathWithName << " modelName: " << m_name << '\n';
}


glm::vec3& Light::LightDefault::getLightPosition()
{
	return m_lightPosition;
}

glm::vec3& Light::LightDefault::getLightColors()
{
	return m_lightColors;
}
