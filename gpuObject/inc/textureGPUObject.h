#pragma once
#include "gpuObjectIf.h"

#include "error.h"

namespace GPUObject
{
class TextureGPUObject : public GPUObjectIf
{
public:
	TextureGPUObject(Common::Error& err, const std::string& name);

	~TextureGPUObject();

	const std::string& getName();

	void preInit();
	void postInit();

private:
	std::string m_name;
};
}