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
	// Put this in separate function
	// ---- [ 1] LOAD ALL TEXTUREs ] ----

	// 1] Get all textures ....png for loading
	std::vector<std::string> vectorOfAllTextureStrings;
	FACTORY.getDatabase()->getRest(m_name, "load", vectorOfAllTextureStrings);
	/*
		_vanquish/textures/texture0.png
		...
		_vanquish/textures/texture5.png
	*/
	// 2] Iterate over string of all textures
	for (auto s : vectorOfAllTextureStrings)
	{
		// 3] Create Raw Texture (only textureName and textureId)
		std::shared_ptr<GPUObject::RawTextureStructure> rawTextureStruct = std::make_shared<GPUObject::RawTextureStructure>(s);
		// 4] Get TextureId
		GLuint tempTextID = createTexture(s);
		// 5] Fill Raw Texture Struct with data
		rawTextureStruct->m_name = s;
		rawTextureStruct->m_textureId = tempTextID;
		// 6] Store each raw texture in Factory Store
		FACTORY.storeInContainer(rawTextureStruct);
	}


	// ---- [ 2] COMBINE ALL TEXTUREs ] ----

	// 1] Get all GPUObjectTexture objects
	std::vector<std::string> vectorOfAllGPUObjectTextureStrings;
	FACTORY.getDatabase()->getRest(m_name, "GPUObjectTexture", vectorOfAllGPUObjectTextureStrings);
	/*
		vanquishGPUObjectTexture
		...
    */
	// 2] Foreach object create GPUObjectTexture and set vector of TextureStructure
	for (auto s : vectorOfAllGPUObjectTextureStrings)
	{
		// ex. vanquishGPUObjectTexture
		m_GPUObjectIfTemp = std::make_shared<GPUObject::TextureGPUObject>(s);

		// TODO: Get last 2 database param and depending on 2nd param fill params in separate method
		std::vector<std::string> vectorOfAllShaderTextures;
		FACTORY.getDatabase()->getRest(s, "defaultShader", vectorOfAllShaderTextures);
		/*
	        NAME0
	        NAME1
			...
        */
		for (auto s : vectorOfAllShaderTextures)
		{
			GPUObject::TextureStructure tempTextureStruct(s);

			std::string tempTexture;
			FACTORY.getDatabase()->getRest(s, "texture", tempTexture);
			/*
				_vanquish/textures/texture1.png
			*/
			std::shared_ptr<GPUObject::RawTextureStructure> tempRawTextureStruct = FACTORY.getRawTextureStructure(tempTexture);
            
			// Get also other params from DB (textureNM, shineDumper, Reflectivity ...)
			tempTextureStruct.m_name = tempRawTextureStruct->m_name;
			tempTextureStruct.m_textureId = tempRawTextureStruct->m_textureId;

			// Store this (for ex defaultShader struct) in vector of structs
			m_GPUObjectIfTemp->setTextureStructInVec(tempTextureStruct);
		}

		FACTORY.storeInContainer("GPUObjectIf", m_GPUObjectIfTemp);
	}

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
