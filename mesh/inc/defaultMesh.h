#pragma once
#include "meshIf.h"

#include "error.h"
#include "shaderIf.h"


namespace Mesh
{
class DefaultMesh : public MeshIf
{
public:
	DefaultMesh(Common::Error& err, const std::string& name);

	~DefaultMesh();

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
std::shared_ptr<Shader::ShaderIf> defaultShaderIf;
};
}