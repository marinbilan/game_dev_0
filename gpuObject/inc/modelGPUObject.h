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
	void setMeshInVec(const MeshStructure& mesh) override;

	// Get
	std::vector<MeshStructure>& getMeshVec() override;

	void info();

private:
	std::string m_name;

	std::vector<MeshStructure> m_vecOfMeshes;
};
} // End of Namespace