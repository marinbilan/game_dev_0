#pragma once
#include "modelIf.h"

#include <memory>
#include "error.h"
#include "meshIf.h"

namespace Model
{
class StaticModel : public ModelIf
{
public:
	StaticModel(Common::Error& err, const std::string& name);

	~StaticModel();

    void render();

	// ModelIf
	void preInit();
	void postInit();

	const std::string& getName() 
	{ 
		return m_name; 
	}

	void cmdPrompt(const std::string& arg0);

private:
std::string m_name;

std::shared_ptr<Mesh::MeshIf> defaultMeshIf0;
};
}