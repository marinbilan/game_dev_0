#pragma once
#include "gpuObjectIf.h"

#include <vector>

#include "error.h"


namespace GPUObject
{
class ModelGPUObject : public GPUObjectIf
{
public:
	ModelGPUObject(const std::string& name);

	~ModelGPUObject();
	
	const std::string& getName();

	void preInit();
	void postInit();

	// Set
	void setVAO(GLuint VAO);

	void setMeshInVec(const Mesh& mesh) override;

	// Get
	GLuint getVAO();

	std::vector<Mesh>& getMeshVec() override;

	void info();

private:
	std::string m_name;
	GLuint m_VAO;

	std::vector<Mesh> m_vecOfMeshes;
};
}