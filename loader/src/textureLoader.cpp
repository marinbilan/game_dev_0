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
}


void Loader::TextureLoader::postInit()
{
	// ---- [ 1] LOAD ALL TEXTUREs AND CREATE RAW TEXTURE OBJECTs] ----
	loadAllTexturesAndCreateRawTextureStructs();
	loadTerrainTexturesAndCreateRawTextureStructs();

	// ---- [ 2] COMBINE ALL TEXTUREs ] ----
	createGPUObjectTextures();
}


// 1.1 STEP
void Loader::TextureLoader::loadAllTexturesAndCreateRawTextureStructs()
{
	// 1] GET all textures ... .png for loading
	std::vector<std::string> vectorOfAllTextureStrings;
	FACTORY.getDatabase()->getRest(m_name, "loadTexture", vectorOfAllTextureStrings);
	/*
		_vanquish/textures/texture0.png
		...
		_vanquish/textures/texture5.png
	*/
	// 2] Iterate over string of all textures
	for (auto s : vectorOfAllTextureStrings)
	{
		// 3] CREATE Raw Texture (only textureName and textureId)
		std::shared_ptr<GPUObject::RawTextureStructure> rawTextureStruct = std::make_shared<GPUObject::RawTextureStructure>(s);
		// 4] GET TextureId
		GLuint tempTextID = createTexture(s);
		// 5] FILL Raw Texture Struct with data
		rawTextureStruct->m_name = s;
		rawTextureStruct->m_textureId = tempTextID;
		// 6] STORE each raw texture in Factory Store
		FACTORY.storeInContainer(rawTextureStruct);
	}
}

// 1.2 STEP
void Loader::TextureLoader::loadTerrainTexturesAndCreateRawTextureStructs()
{
	// 1] GET all textures ... .png for loading
	std::vector<std::string> vectorOfAllTerrainTextureStrings;
	FACTORY.getDatabase()->getRest(m_name, "loadTerrainTexture", vectorOfAllTerrainTextureStrings);
	/*
		_src/textures/grass.png
		...
		_src/textures/blendMap2.png
	*/
	// 2] Iterate over string of all textures
	for (auto s : vectorOfAllTerrainTextureStrings)
	{
		// 3] CREATE Raw Texture (only textureName and textureId)
		std::shared_ptr<GPUObject::RawTextureStructure> rawTextureStruct = std::make_shared<GPUObject::RawTextureStructure>(s);
		// 4] GET TextureId
		GLuint tempTextID = createTerrainTexture(s);
		// 5] FILL Raw Texture Struct with data
		rawTextureStruct->m_name = s;
		rawTextureStruct->m_textureId = tempTextID;
		// 6] STORE each raw texture in Factory Store
		FACTORY.storeInContainer(rawTextureStruct);
	}
}


// 2.1 STEP
void Loader::TextureLoader::createGPUObjectTextures()
{
	// 1] Get all GPUObjectTexture objects
	std::vector<std::string> vectorOfAllGPUObjectTextureStrings;
	FACTORY.getDatabase()->getRest(m_name, "GPUObjectTexture", vectorOfAllGPUObjectTextureStrings);
	/*
		vanquishGPUObjectTexture
		...
		terrainGPUObjectTexture
	*/
	// 2] ForEach object create GPUObjectTexture and set vector of TextureStructure
	for (auto s : vectorOfAllGPUObjectTextureStrings)
	{
		m_GPUObjectIfTemp = std::make_shared<GPUObject::TextureGPUObject>(s);

		std::vector<std::string> vectorOfShadersTypes;
		std::vector<std::string> vectorOfShaderNames;
		FACTORY.getDatabase()->getColumnOfStrings12(s, vectorOfShadersTypes, vectorOfShaderNames);
		/*
		    //                          // Shader Type   // Shader Name
			vanquishGPUObjectTexture    defaultShader    NAME0
			vanquishGPUObjectTexture    defaultShader    NAME0

			terrainGPUObjectTexture     terrainShader    TERRAINNAME0
			...
		*/
		std::vector<std::string>::iterator it = vectorOfShaderNames.begin();
		for (auto s : vectorOfShadersTypes)
		{	
			if (!s.compare("defaultShader"))
			{
				/*
					NAME0
					NAME1
					...
				*/
				createDefaultShader(*it);
			}
			else if (!s.compare("terrainShader"))
			{
				/*
					TERRAINNAME0
					...
				*/
				createTerrainShader(*it);
			}
			++it;
		}

		FACTORY.storeInContainer("GPUObjectIf", m_GPUObjectIfTemp);
	}
}


void Loader::TextureLoader::createDefaultShader(const std::string& defaultShaderName)
{
	GPUObject::TextureStructure tempTextureStruct(defaultShaderName);

	std::string tempTexture;
	FACTORY.getDatabase()->getRest(defaultShaderName, "texture", tempTexture);
	/*
		_vanquish/textures/texture0.png
	*/
	GLfloat shineDumper;
	FACTORY.getDatabase()->getFloat21(defaultShaderName, "shineDumper", shineDumper);
	/*
		shineDumper
	*/
	GLfloat reflectivity;
	FACTORY.getDatabase()->getFloat21(defaultShaderName, "reflectivity", reflectivity);
	/*
		reflectivity
	*/

	std::shared_ptr<GPUObject::RawTextureStructure> tempRawTextureStruct = FACTORY.getRawTextureStructure(tempTexture);

	tempTextureStruct.m_name = tempRawTextureStruct->m_name;
	tempTextureStruct.m_textureId = tempRawTextureStruct->m_textureId;
	tempTextureStruct.m_shineDamper = shineDumper;
	tempTextureStruct.m_reflectivity = reflectivity;

	// Store this (for ex defaultShader struct) in vector of structs
	m_GPUObjectIfTemp->setTextureStructInVec(tempTextureStruct);
}


void Loader::TextureLoader::createTerrainShader(const std::string& defaultShaderName)
{
	GPUObject::TextureStructure tempTextureStruct(defaultShaderName);

	std::string texture0;
	std::string texture1;
	std::string texture2;
	std::string texture3;
	std::string texture4;
	FACTORY.getDatabase()->getRest(defaultShaderName, "texture0", texture0);
	FACTORY.getDatabase()->getRest(defaultShaderName, "texture1", texture1);
	FACTORY.getDatabase()->getRest(defaultShaderName, "texture2", texture2);
	FACTORY.getDatabase()->getRest(defaultShaderName, "texture3", texture3);
	FACTORY.getDatabase()->getRest(defaultShaderName, "texture4", texture4);
	/*
		_src/textures/grass.png        // texture0
		...
		_src/textures/blendMap2.png    // texture4
	*/
	GLfloat shineDumper;
	FACTORY.getDatabase()->getFloat21(defaultShaderName, "shineDumper", shineDumper);
	/*
		shineDumper
	*/
	GLfloat reflectivity;
	FACTORY.getDatabase()->getFloat21(defaultShaderName, "reflectivity", reflectivity);
	/*
		reflectivity
	*/

	std::shared_ptr<GPUObject::RawTextureStructure> tempRawTextureStruct0 = FACTORY.getRawTextureStructure(texture0);
	std::shared_ptr<GPUObject::RawTextureStructure> tempRawTextureStruct1 = FACTORY.getRawTextureStructure(texture1);
	std::shared_ptr<GPUObject::RawTextureStructure> tempRawTextureStruct2 = FACTORY.getRawTextureStructure(texture2);
	std::shared_ptr<GPUObject::RawTextureStructure> tempRawTextureStruct3 = FACTORY.getRawTextureStructure(texture3);
	std::shared_ptr<GPUObject::RawTextureStructure> tempRawTextureStruct4 = FACTORY.getRawTextureStructure(texture4);

	// Common stuff
	tempTextureStruct.m_name = tempRawTextureStruct0->m_name;
	tempTextureStruct.m_textureId = tempRawTextureStruct0->m_textureId;
	std::cout << " --------> texture0: " << tempRawTextureStruct0->m_textureId << '\n';
	// Terrain stuff
	tempTextureStruct.m_nameName1 = tempRawTextureStruct1->m_name;
	tempTextureStruct.m_texture1 = tempRawTextureStruct1->m_textureId;
	std::cout << " --------> texture1: " << tempRawTextureStruct1->m_textureId << '\n';

	tempTextureStruct.m_nameName2 = tempRawTextureStruct2->m_name;
	tempTextureStruct.m_texture2 = tempRawTextureStruct2->m_textureId;
	std::cout << " --------> texture2: " << tempRawTextureStruct2->m_textureId << '\n';

	tempTextureStruct.m_nameName3 = tempRawTextureStruct3->m_name;
	tempTextureStruct.m_texture3 = tempRawTextureStruct3->m_textureId;
	std::cout << " --------> texture3: " << tempRawTextureStruct3->m_textureId << '\n';

	tempTextureStruct.m_nameName4 = tempRawTextureStruct4->m_name;
	tempTextureStruct.m_texture4 = tempRawTextureStruct4->m_textureId;
	std::cout << " --------> texture4: " << tempRawTextureStruct4->m_textureId << '\n';

	// Terrain property
	tempTextureStruct.m_shineDamper = shineDumper;
	tempTextureStruct.m_reflectivity = reflectivity;

	// Store this (for ex defaultShader struct) in vector of structs
	m_GPUObjectIfTemp->setTextureStructInVec(tempTextureStruct);
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


GLuint Loader::TextureLoader::createTerrainTexture(const std::string& _textureName)
{
	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN; //pointer to the image, once loaded
	FIBITMAP* dib(0);                    //pointer to the image data
	BYTE* bits(0);                       //image width and height
	unsigned int width(0), height(0);    //OpenGL's image ID to map to
	GLuint gl_texID;

	fif = FreeImage_GetFileType(_textureName.c_str(), 0);
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(_textureName.c_str());

	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, _textureName.c_str());

	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

	// Novo
	RGBQUAD color;
	FreeImage_GetPixelColor(dib, 20, 20, &color);
	int heightImag = FreeImage_GetHeight(dib);

	//generate an OpenGL texture ID for this texture
	glGenTextures(1, &gl_texID);
	//bind to the new texture ID
	glBindTexture(GL_TEXTURE_2D, gl_texID);
	//store the texture data for OpenGL use

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits); // bits = imageData
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmpWidth, bmpHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -1.5);

	//Free FreeImage's copy of the data
	FreeImage_Unload(dib);

	//return success
	return gl_texID;
}