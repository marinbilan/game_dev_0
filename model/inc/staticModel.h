#pragma once
#include "modelIf.h"

#include <vector>
#include <memory>
#include "error.h"

//#include "gpuObjectIf.h"
//#include "meshIf.h"

namespace Model
{
class StaticModel : public ModelIf
{
public:
	StaticModel(Common::Error& err, const std::string& name);

	~StaticModel();

	// ModelIf
	void preInit();
	void postInit();

	void setGPUObject(const std::shared_ptr<GPUObject::GPUObjectIf>& gpuObjectIf);
	void setMesh(const std::shared_ptr<Mesh::MeshIf>& meshIf);

    void render();

	const std::string& getName() 
	{ 
		return m_name; 
	}

	void cmdPrompt(const std::string& arg0);

private:
std::string m_name;

GLuint m_VAO;

std::shared_ptr<GPUObject::GPUObjectIf> m_gpuObjectIf;
std::vector<std::shared_ptr<Mesh::MeshIf>> m_vecOfdefaultMeshIf;
};
}