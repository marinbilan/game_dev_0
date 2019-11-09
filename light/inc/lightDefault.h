#pragma once

#include "lightIf.h"

namespace Light
{
class LightDefault : public LightIf
{
public:
	LightDefault(const std::string& name);
	LightDefault(const std::string& dbPath, const std::string& name);

	~LightDefault();

	const std::string& getName()
	{
		return m_name;
	}

	void preInitialization();
	void postInitialization();

	glm::vec3& getLightPosition();
	glm::vec3& getLightColors();

	virtual void dump();
	virtual void cmdPrompt(const std::string& arg0);

private:
std::string m_dbPath;
std::string m_dbPathWithName;
std::string m_name;

glm::vec3 m_lightPosition;
glm::vec3 m_lightColors;
};
}