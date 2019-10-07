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
void Camera::CameraDefault::preInitialization()
{
	// GET light position and light color from DB
}


void Camera::CameraDefault::postInitialization()
{
	// Get Camera position and create viewMatrix
}


glm::vec3& Light::LightDefault::getLightPosition()
{
	return m_lightPosition;
}

glm::vec3& Light::LightDefault::getLightColors()
{
	return m_lightColors;
}
