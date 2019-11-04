#pragma once
#include "gpuObjectIf.h"


namespace GPUObject
{
class TextureGPUObject : public GPUObjectIf
{
public:
	TextureGPUObject(const std::string& name);
	TextureGPUObject(const std::string& dbPath, const std::string& name);

	~TextureGPUObject();

	const std::string& getName();

	void preInit();
	void postInit();

	// ========================================================================================
    // NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION
    // ========================================================================================
	void preInitialization();
	void postInitialization();

	// Set
	void setTextureStructInVec(const TextureStructure& textureStruct) override;

	// Get
	std::vector<TextureStructure>& getTextureStructVec() override;

	void info();

private:
	std::string m_dbPath;
	std::string m_dbPathWithName;
	std::string m_name;

	std::vector<TextureStructure> m_vecOfTextures;
};
} // End of Namespace