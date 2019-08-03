#include "lightDefault.h"
#include "factory.h"

Light::LightDefault::LightDefault(const std::string& name) : m_name(name)
{
	preInit();
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

glm::vec3& Light::LightDefault::getLightPosition()
{
	return m_lightPosition;
}

glm::vec3& Light::LightDefault::getLightColors()
{
	return m_lightColors;
}
