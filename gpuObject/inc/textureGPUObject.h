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

	void setTextureID(GLuint textureID);
	GLuint getTextureID();

private:
	std::string m_name;
	GLuint m_textureID;
};
}