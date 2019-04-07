#pragma once
#include "gpuObjectIf.h"

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

private:
	std::string m_name;
};
}