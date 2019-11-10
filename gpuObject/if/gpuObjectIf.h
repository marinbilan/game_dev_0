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
		m_terrainTexture1Id(0),
		m_terrainTexture2Id(0),
		m_terrainTexture3Id(0),
		m_terrainTexture4Id(0),
		m_shineDamper(0.0),
		m_reflectivity(0.0) {};

	void dump()
	{
		if (m_textureId != 0) std::cout << "|| Texture Name: " << m_textureIdName << " |TextureId: " << m_textureId << '\n';
		if(m_textureNormalMapId != 0) std::cout << "|| TextureNM name: " << m_textureNormalMapName << " |TextureNMId: " << m_textureNormalMapId << '\n';
	
		if (m_terrainTexture1Id != 0) std::cout << "|| m_terrainTexture1Name name: " << m_terrainTexture1Name << " |m_terrainTexture1Id: " << m_terrainTexture1Id << '\n';
		if (m_terrainTexture2Id != 0) std::cout << "|| m_terrainTexture2Name name: " << m_terrainTexture2Name << " |m_terrainTexture2Id: " << m_terrainTexture2Id << '\n';
		if (m_terrainTexture3Id != 0) std::cout << "|| m_terrainTexture3Name name: " << m_terrainTexture3Name << " |m_terrainTexture3Id: " << m_terrainTexture3Id << '\n';
		if (m_terrainTexture4Id != 0) std::cout << "|| m_terrainTexture4Name name: " << m_terrainTexture4Name << " |m_terrainTexture4Id: " << m_terrainTexture4Id << '\n';

		if (m_shineDamper != 0)  std::cout << "|| m_shineDamper: " << m_shineDamper << '\n';
		if (m_reflectivity != 0) std::cout << "|| m_reflectivity: " << m_reflectivity << '\n';
	}

std::string m_name;

// Texture
std::string m_textureIdName;
GLuint m_textureId;
// NormalMap Texture
std::string m_textureNormalMapName;
GLuint m_textureNormalMapId;

// Terrain Textures
std::string m_terrainTexture1Name;
GLuint m_terrainTexture1Id;

std::string m_terrainTexture2Name;
GLuint m_terrainTexture2Id;

std::string m_terrainTexture3Name;
GLuint m_terrainTexture3Id;

std::string m_terrainTexture4Name;
GLuint m_terrainTexture4Id;
// --

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