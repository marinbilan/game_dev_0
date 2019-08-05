#pragma once
#include <iostream>
#include <vector>

#include "glew.h"


namespace GPUObject
{

struct MeshStructure
{
	MeshStructure(const std::string& name) : m_name(name) {};

	std::string& getName()
	{
		return m_name;
	}

std::string m_name;

GLuint m_VAO;
GLuint m_VBO;
GLuint m_IBO;
GLuint m_NumOfInds;
};


// Raw Texture - goes in pool of textures
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

std::string m_name;

GLuint m_textureId;

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

	// Mesh
	virtual void setMeshInVec(const MeshStructure& mesh) {}

	virtual std::vector<MeshStructure>& getMeshVec()
	{ 
		return dummy;
	}

	// Texture
	virtual void setTextureStructInVec(const TextureStructure& textureStruct) {}

	virtual std::vector<TextureStructure>& getTextureStructVec()
	{
		return dummyTextureVector;
	}

	virtual void info() {}

private:

std::vector<MeshStructure> dummy;
std::vector<TextureStructure> dummyTextureVector;
};
}