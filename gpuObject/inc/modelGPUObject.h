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

	void preInitialization();
	void postInitialization();

	// Set
	void setMeshInVec(const MeshStructure& mesh) override;

	// Get
	std::vector<MeshStructure>& getMeshVec() override;

	void info();

private:
	std::string m_dbPath;
	std::string m_dbPathWithName;
	std::string m_name;

	std::vector<MeshStructure> m_vecOfMeshes;
};
} // End of Namespace