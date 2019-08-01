#pragma once
#include "gpuObjectIf.h"

#include <vector>


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
	void setMeshInVec(const Mesh& mesh) override;

	// Get
	std::vector<Mesh>& getMeshVec() override;

	void info();

private:
	std::string m_name;

	std::vector<Mesh> m_vecOfMeshes;
};
} // End of Namespace