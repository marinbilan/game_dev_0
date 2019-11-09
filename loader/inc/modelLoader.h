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
	ModelLoader(const std::string& dbPath, const std::string& name);

	~ModelLoader();

	const std::string& getName();

	void preInitialization();
	void postInitialization();

	void loadModelNew(const std::vector<std::string>& vecModelsForLoad);
	void initSceneNew(const aiScene* _pScene);

private:
std::string m_dbPath;
std::string m_dbPathWithName;
std::string m_name;

std::vector<std::string> m_vecModelsPath;
std::vector<std::string> m_vecMeshAttribs;

	void loadModel();	
	void initScene(const aiScene* _pScene);
	void initMesh(const std::string& meshName, GLuint _index, const aiMesh* _paiMesh);
	void initNormalMapMesh(const std::string& meshName, GLuint _index, const aiMesh* _paiMesh);

	std::vector<std::string> m_meshStructNameTempVec;
	GLuint m_VAO;

	const aiScene*    pScene;

	std::shared_ptr<GPUObject::GPUObjectIf> m_GPUObjectIf;
};
}