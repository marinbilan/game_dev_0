#include "textureLoader.h"

#include "factory.h"


Loader::TextureLoader::TextureLoader(const std::string& name) : m_name(name)
{
}


Loader::TextureLoader::~TextureLoader()
{
}


const std::string& Loader::TextureLoader::getName()
{
	return m_name;
}


void Loader::TextureLoader::preInit()
{
	Common::Error err;
	
	// Test GPU Texture object
	std::string GPUTextureObjectString;
	// TODO: Get column (vector) of this objects
	FACTORY.getDatabase()->getStringFromDB(m_name, "GPUObjectTexture", GPUTextureObjectString);

	std::vector<std::string> wantedString;
	FACTORY.getDatabase()->getRest(m_name, GPUTextureObjectString, wantedString);

	m_GPUObjectIfTemp = std::make_shared<GPUObject::TextureGPUObject>(GPUTextureObjectString);

	for (auto s : wantedString)
	{
		// Store Stuff
		GPUObject::TextureStructure tempTextureStruct(s);

		GLuint tempTextID = createTexture(s);
		tempTextureStruct.m_textureId = tempTextID;

		m_GPUObjectIfTemp->setTextureStructInVec(tempTextureStruct);
		// TODO: Store each texture in pool of textures!
	}

	FACTORY.storeInContainer("GPUObjectIf", m_GPUObjectIfTemp);
}


void Loader::TextureLoader::postInit()
{
}


GLuint Loader::TextureLoader::createTexture(const std::string& _textureName)
{
	width = 0;
	height = 0;

	fif = FIF_UNKNOWN;
	dib = 0;
	bits = 0;

	fif = FreeImage_GetFileType(_textureName.c_str(), 0);

	if (fif == FIF_UNKNOWN)
	{
		fif = FreeImage_GetFIFFromFilename(_textureName.c_str());
		std::cout << "FIF UNKNOWN!!!!" << std::endl;
	}
	if (FreeImage_FIFSupportsReading(fif)) dib = FreeImage_Load(fif, _textureName.c_str());

	bits = FreeImage_GetBits(dib);
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	FreeImage_FlipVertical(dib);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Anisotropic Filtering
	aniso = 4.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);

	FreeImage_Unload(dib);

	return textureID;
}
