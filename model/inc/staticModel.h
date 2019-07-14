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

	const std::string& getName() 
	{ 
		return m_name; 
	}

	// ModelIf
	void preInit();
	void postInit();

    void render();

	void cmdPrompt(const std::string& arg0);

private:
std::string m_name;
GLuint m_VAO;

glm::vec3                 m_modelPosition;
glm::vec3                 m_modelScale;
glm::vec3                 m_modelRotateAround;
GLfloat                   m_angle;

glm::mat4                 m_modelMatrix;

std::shared_ptr<GPUObject::GPUObjectIf>    m_gpuObjectIf;
std::vector<std::shared_ptr<Mesh::MeshIf>> m_vecOfdefaultMeshIf;
};
} // end of namespace