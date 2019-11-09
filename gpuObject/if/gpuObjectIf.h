#pragma once
#include <iostream>
#include <vector>

#include "glew.h"


namespace GPUObject
{

struct MeshStructure
{
public:
	MeshStructure(const std::string& name) : m_name(name) {};

	std::string& getName()
	{
		return m_name;
	}

	void dump()
	{
		std::cout << "|| Mesh Name: " << m_name << " |VAO: " << m_VAO << " |VBO: " << m_VBO << " |IBO: " << m_IBO << " |numOfInds: " << m_NumOfInds << '\n';
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
	TextureStructure(const std::string& name) : 
		m_name(name), 
		m_textureId(0),
		m_textureNormalMapId(0),
		m_texture1Id(0),
		m_texture2Id(0),
		m_texture3Id(0),
		m_texture4Id(0),
		m_shineDamper(0.0),
		m_reflectivity(0.0) {};

	void dump()
	{
		if (m_textureId != 0) std::cout << "|| Texture Name: " << m_textureIdName << " |TextureId: " << m_textureId << '\n';
		if(m_textureNormalMapId != 0) std::cout << "|| TextureNM name: " << m_name << " |TextureNMId: " << m_textureNormalMapId << '\n';
	
		if (m_texture1Id != 0) std::cout << "|| m_texture1 name: " << m_nameName1 << " |m_texture1Id: " << m_texture1Id << '\n';
		if (m_texture2Id != 0) std::cout << "|| m_texture2 name: " << m_nameName2 << " |m_texture2Id: " << m_texture2Id << '\n';
		if (m_texture3Id != 0) std::cout << "|| m_texture3 name: " << m_nameName3 << " |m_texture3Id: " << m_texture3Id << '\n';
		if (m_texture4Id != 0) std::cout << "|| m_texture4 name: " << m_nameName4 << " |m_texture4Id: " << m_texture4Id << '\n';

		if (m_shineDamper != 0)  std::cout << "|| m_shineDamper: " << m_shineDamper << '\n';
		if (m_reflectivity != 0) std::cout << "|| m_reflectivity: " << m_reflectivity << '\n';
	}

std::string m_name;

// Texture
std::string m_textureIdName;
GLuint m_textureId;
// NormalMap Texture
std::string m_textureNormalMapIdName;
GLuint m_textureNormalMapId;

// Terrain Texture Ids
std::string m_nameName1;
GLuint m_texture1Id;

std::string m_nameName2;
GLuint m_texture2Id;

std::string m_nameName3;
GLuint m_texture3Id;

std::string m_nameName4;
GLuint m_texture4Id;

GLfloat m_shineDamper;
GLfloat m_reflectivity;
};


class GPUObjectIf
{
public:
	~GPUObjectIf()
	{
	}

	virtual const std::string& getName()
	{
		return "nameFromInterface";
	}

	virtual void preInit() {};
	virtual void postInit() {};

	// ========================================================================================
    // NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION
    // ========================================================================================
	virtual void preInitialization() {};
	virtual void postInitialization() {};

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

std::vector<MeshStructure>    dummy;
std::vector<TextureStructure> dummyTextureVector;
};
}