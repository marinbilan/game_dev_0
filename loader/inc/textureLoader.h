#pragma once
#include "loaderIf.h"

#include "error.h"


namespace Loader
{
class TextureLoader : public LoaderIf
{
public:
	TextureLoader(Common::Error& err, const std::string& name);

	~TextureLoader();

	const std::string& getName();

	void preInit();
	void postInit();
	
	GLuint createTexture(std::string& _textureName);
	
private:
	std::string m_name;

	GLuint textureID;

	GLuint            width;
	GLuint            height;
	FREE_IMAGE_FORMAT fif;
	FIBITMAP*         dib;   // Pointer to the image data
	BYTE*             bits;  // Image width and height
	GLfloat           aniso; // Anisotropic Filtering Parameters
};
}