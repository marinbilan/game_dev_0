#pragma once
#include "loaderIf.h"

#include "gpuObjectIf.h"
#include "modelGPUObject.h"

#include "error.h"

namespace Loader
{

struct Vert
{
public:
	Vert(glm::vec3 position, glm::vec2 textureCoord, glm::vec3 normal) : 
	m_position(position),
	m_texCoords(textureCoord),
	m_normal(normal)
	{
	}

private:
	glm::vec3 m_position;
	glm::vec2 m_texCoords;
	glm::vec3 m_normal;
};


struct VertNormalMap
{
public:
	VertNormalMap(glm::vec3 position, glm::vec2 textureCoord, glm::vec3 normal, glm::vec3 tangemt) :
		m_position(position),
		m_texCoords(textureCoord),
		m_normal(normal),
		m_tangent(tangemt)
	{
	}

private:
	glm::vec3 m_position;
	glm::vec2 m_texCoords;
	glm::vec3 m_normal;
	glm::vec3 m_tangent;
};


class ModelLoader : public LoaderIf
{
public:
	ModelLoader(const std::string& name);

	~ModelLoader();

	const std::string& getName();

	void preInit();
	void postInit();

private:
	void loadModel();	
	void initScene(const aiScene* _pScene);
	void initMesh(const std::string& meshName, GLuint _index, const aiMesh* _paiMesh);
	void initNormalMapMesh(const std::string& meshName, GLuint _index, const aiMesh* _paiMesh);
	
	std::string m_name;

	std::vector<std::string> m_meshStructNameTempVec;
	GLuint m_VAO;

	const aiScene*    pScene;

	std::shared_ptr<GPUObject::GPUObjectIf> m_GPUObjectIf;
};
}