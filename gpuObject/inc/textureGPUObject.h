#pragma once
#include "gpuObjectIf.h"

#include "error.h"

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

	void setTextureID(GLuint textureID);
	GLuint getTextureID();

	void setTextureStructInVec(const TextureStructure& textureStruct) override;

	// Get
	std::vector<TextureStructure>& getTextureStructVec() override;

private:
	std::string m_name;
	GLuint m_textureID;

	std::vector<TextureStructure> m_vecOfTextures;
};
}