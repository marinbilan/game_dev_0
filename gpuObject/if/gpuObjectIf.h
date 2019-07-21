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

struct TextureStructure
{
	TextureStructure(const std::string& name) : m_name(name) {};

GLuint m_textureId;

private:
std::string m_name;
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

	// Get
	virtual GLuint getVAO()
	{
		return 0;
	}

	virtual std::vector<Mesh>& getMeshVec() 
	{ 
		return dummy;
	}


	// TEXTURE STUFF
	virtual void setTextureID(GLuint textureID) {}
	virtual GLuint getTextureID() { return 0; }

	virtual void info() {}

	std::vector<Mesh> dummy;
};
}