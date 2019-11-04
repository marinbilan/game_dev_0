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
		std::cout << " mesh name  : " << m_name << '\n';
		std::cout << "  VAO       : " << m_VAO << '\n';
		std::cout << "   VBO      : " << m_VBO << '\n';
		std::cout << "   IBO      : " << m_IBO << '\n';
		std::cout << "   numOfInds: " << m_NumOfInds << '\n';
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

	void dump()
	{
		std::cout << " Texture   name : " << m_name << " TextureId    : " << m_textureId << '\n';
		//std::cout << " TextureNM name : " << m_name << " TextureNMId    : " << m_textureNormalMapId << '\n';

		//std::cout << " Texture1 name : " << m_nameName1 << " Texture1Id    : " << m_texture1 << '\n';
		//std::cout << " Texture2 name : " << m_nameName2 << " Texture2Id    : " << m_texture2 << '\n';
		//std::cout << " Texture3 name : " << m_nameName3 << " Texture3Id    : " << m_texture3 << '\n';
		//std::cout << " Texture4 name : " << m_nameName4 << " Texture4Id    : " << m_texture4 << '\n';

		std::cout << " Shine Dumper  : " << m_shineDamper << '\n';
		std::cout << " Reflectivity  : " << m_reflectivity << '\n';
	}

std::string m_name;
GLuint m_textureId;
// NormalMap Texture
GLuint m_textureNormalMapId;

// Terrain Texture Ids
std::string m_nameName1;
GLuint m_texture1;
std::string m_nameName2;
GLuint m_texture2;
std::string m_nameName3;
GLuint m_texture3;
std::string m_nameName4;
GLuint m_texture4;

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