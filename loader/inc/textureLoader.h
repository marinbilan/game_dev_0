#pragma once
#include "loaderIf.h"

#include "textureGPUObject.h"


namespace Loader
{
class TextureLoader : public LoaderIf
{
public:
	TextureLoader(const std::string& name);

	~TextureLoader();

	const std::string& getName();

	void preInit();
	void postInit();
	
	GLuint createTexture(const std::string& _textureName);
	
private:
	std::string m_name;

	std::shared_ptr<GPUObject::GPUObjectIf> m_GPUObjectIfTemp;

	GLuint textureID;

	GLuint            width;
	GLuint            height;
	FREE_IMAGE_FORMAT fif;
	FIBITMAP*         dib;   // Pointer to the image data
	BYTE*             bits;  // Image width and height
	GLfloat           aniso; // Anisotropic Filtering Parameters
};
}