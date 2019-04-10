#pragma once
#include "gpuObjectIf.h"

#include <vector>

#include "error.h"


namespace GPUObject
{
class ModelGPUObject : public GPUObjectIf
{
public:
	ModelGPUObject(Common::Error& err, const std::string& name);

	~ModelGPUObject();
	
	const std::string& getName();

	void preInit();
	void postInit();

	// modelGPUObjectIf
	void setVAO(GLuint VAO);

	void setVBO(GLuint VBO);

	void setIBO(GLuint IBO);

	void info();

private:
	std::string m_name;

	GLuint m_VAO;
	std::vector<GLuint> m_vecOfVBOs;
	std::vector<GLuint> m_vecOfIBOs;
};
}