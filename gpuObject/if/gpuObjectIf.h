#pragma once
#include <iostream>
#include <vector>

#include "glew.h"


namespace GPUObject
{

struct Mesh
{
GLuint m_VBO;
GLuint m_IBO;
GLuint m_NumOfInds;
};

// Raw Texture - goes in pool of textures
// Can be any kind of texture (ordinary, normal map, specular ...)
struct RawTextureStructure
{
	RawTextureStructure(const std::string& name) : m_name(name) {};

	std::string& getName()
	{
		return m_name;
	}

std::string m_name;
GLuint m_textureId;
};

// For each mesh
struct TextureStructure
{
	TextureStructure(const std::string& name) : m_name(name) {};

GLuint m_textureId;
std::string m_name;
// Texture parameters
GLuint m_shineDamper;
GLuint m_reflectivity;
};


class GPUObjectIf
{
public:
	~GPUObjectIf()
	{
	}

	virtual const std::string& getName()
	{
		return "nameFromInterfaca";
	}

	virtual void preInit() {};
	virtual void postInit() {};

	// Set
	virtual void setVAO(GLuint VAO)
	{
	}

	virtual void setMeshInVec(const Mesh& mesh) {}
	virtual void setTextureStructInVec(const TextureStructure& textureStruct) {}

	// Get
	virtual GLuint getVAO()
	{
		return 0;
	}

	virtual std::vector<Mesh>& getMeshVec() 
	{ 
		return dummy;
	}

	virtual std::vector<TextureStructure>& getTextureStructVec()
	{
		return dummyTextureVector;
	}

	// TEXTURE STUFF
	virtual void setTextureID(GLuint textureID) {}
	virtual GLuint getTextureID() { return 0; }

	virtual void info() {}

	std::vector<Mesh> dummy;
	std::vector<TextureStructure> dummyTextureVector;
};
}