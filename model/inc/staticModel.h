#pragma once
#include "modelIf.h"

#include <vector>
#include <memory>
#include "error.h"


namespace Model
{
class StaticModel : public ModelIf
{
public:
	StaticModel(const std::string& name);

	~StaticModel();

	// ModelIf
	void preInit();
	void postInit();

	void setGPUObject(const std::shared_ptr<GPUObject::GPUObjectIf>& gpuObjectIf);
	void setMesh(const std::shared_ptr<Mesh::MeshIf>& meshIf);

	void connect();

    void render();

	const std::string& getName() 
	{ 
		return m_name; 
	}

	void cmdPrompt(const std::string& arg0);

private:
std::string m_name;

glm::mat4                 modelMatrix;

glm::vec3                 modelPosition;
glm::vec3                 modelScale;
glm::vec3                 modelRotateAround;
GLfloat                   angle;

GLuint m_VAO;

std::shared_ptr<GPUObject::GPUObjectIf> m_gpuObjectIf;
std::vector<std::shared_ptr<Mesh::MeshIf>> m_vecOfdefaultMeshIf;

std::shared_ptr<Mesh::MeshIf> m_meshIf;
};
}