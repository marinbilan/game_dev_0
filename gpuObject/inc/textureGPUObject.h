#pragma once
#include "gpuObjectIf.h"


namespace GPUObject
{
class TextureGPUObject : public GPUObjectIf
{
public:
	TextureGPUObject(const std::string& name);

	~TextureGPUObject();

	const std::string& getName();

	void preInit();
	void postInit();

	// Set
	void setTextureStructInVec(const TextureStructure& textureStruct) override;

	// Get
	std::vector<TextureStructure>& getTextureStructVec() override;

private:
	std::string m_name;

	std::vector<TextureStructure> m_vecOfTextures;
};
} // End of Namespace