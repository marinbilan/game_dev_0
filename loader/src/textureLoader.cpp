#include "textureLoader.h"

#include "factory.h"
//#include "error.h"


Loader::TextureLoader::TextureLoader(const std::string& name) : m_name(name)
{
	std::cout << "TextureLoader created!" << std::endl;
}


Loader::TextureLoader::~TextureLoader()
{
	std::cout << "TextureLoader destructor called!" << std::endl;
}


const std::string& Loader::TextureLoader::getName()
{
	return m_name;
}


void Loader::TextureLoader::preInit()
{
	Common::Error err;

	std::vector<std::string> wantedString;
	FACTORY.getDatabase()->getRest(m_name, "load", wantedString);

	for (auto s : wantedString)
	{
		GLuint tempTextureID = createTexture(s);

		m_GPUObjectIf = std::make_shared<GPUObject::TextureGPUObject>(s);
		m_GPUObjectIf->setTextureID(tempTextureID);

		FACTORY.storeInContainer("GPUObjectIf", m_GPUObjectIf);
	}
	//std::cout << " ------------------------------------ wantedString: " << wantedString[0] << '\n';
	//std::cout << " ------------------------------------ wantedString: " << wantedString[1] << '\n';
	//std::cout << " ------------------------------------ wantedString: " << wantedString[2] << '\n';

	// 0]
	/*
	GLuint tempTextureID = createTexture("_vanquish/textures/texture0.png");

	// createTexture("_vanquish/textures/texture1.png");


	// 1]
	tempTextureID = createTexture("_vanquish/textures/texture1.png");
	m_GPUObjectIf = std::make_shared<GPUObject::TextureGPUObject>(err, "_vanquish/textures/texture1.png");
	m_GPUObjectIf->setTextureID(tempTextureID);
	std::cout << " ------------------------------------ " << tempTextureID << '\n';
	FACTORY.storeInContainer("GPUObjectIf", m_GPUObjectIf);



	// 2]
	tempTextureID = createTexture("_vanquish/textures/texture2.png");
	m_GPUObjectIf = std::make_shared<GPUObject::TextureGPUObject>(err, "_vanquish/textures/texture2.png");
	m_GPUObjectIf->setTextureID(tempTextureID);
	std::cout << " ------------------------------------ " << tempTextureID << '\n';
	FACTORY.storeInContainer("GPUObjectIf", m_GPUObjectIf);




	//createTexture("_vanquish/textures/texture3.png");
	// 3]
	tempTextureID = createTexture("_vanquish/textures/texture3.png");
	m_GPUObjectIf = std::make_shared<GPUObject::TextureGPUObject>(err, "_vanquish/textures/texture3.png");
	m_GPUObjectIf->setTextureID(tempTextureID);
	std::cout << " ------------------------------------ " << tempTextureID << '\n';
	FACTORY.storeInContainer("GPUObjectIf", m_GPUObjectIf);





	//createTexture("_vanquish/textures/texture4.png");
	// 4]
	tempTextureID = createTexture("_vanquish/textures/texture4.png");
	m_GPUObjectIf = std::make_shared<GPUObject::TextureGPUObject>(err, "_vanquish/textures/texture4.png");
	m_GPUObjectIf->setTextureID(tempTextureID);
	std::cout << " ------------------------------------ " << tempTextureID << '\n';
	FACTORY.storeInContainer("GPUObjectIf", m_GPUObjectIf);



	// createTexture("_vanquish/textures/texture5.png");
	// 5]
	tempTextureID = createTexture("_vanquish/textures/texture5.png");
	m_GPUObjectIf = std::make_shared<GPUObject::TextureGPUObject>(err, "_vanquish/textures/texture5.png");
	m_GPUObjectIf->setTextureID(tempTextureID);
	std::cout << " ------------------------------------ " << tempTextureID << '\n';
	FACTORY.storeInContainer("GPUObjectIf", m_GPUObjectIf);
	*/
}





void Loader::TextureLoader::postInit()
{
	std::cout << "postInit function called!" << std::endl;
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
