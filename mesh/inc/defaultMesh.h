#pragma once
#include "meshIf.h"

#include "error.h"
// #include "shaderIf.h"


namespace Mesh
{
class DefaultMesh : public MeshIf
{
public:
	DefaultMesh(Common::Error& err, const std::string& name);

	~DefaultMesh();

	// ModelIf
	void preInit();
	void postInit();

	void setShader(const std::shared_ptr<Shader::ShaderIf>& shaderIf);

	void shaderIdsInit();

	void render();

	const std::string& getName() 
	{ 
		return m_name; 
	}

	void cmdPrompt(const std::string& arg0);

private:
std::string m_name;
std::shared_ptr<Shader::ShaderIf> m_shaderIf;

// Shader Variables
// glm::mat4   projectionMatrix;


// ---- Shader IDs ----
// VERTEX SHADER
GLuint positionsID;
GLuint textureCoordsID;
GLuint normalsID;

GLuint projectionMatrixID;
GLuint viewMatrixID;
GLuint viewMatrixInvID;
GLuint modelMatrixID;

GLuint lightPositionID;
GLuint planeID;

// FRAGMENT SHADER
GLuint lightColourID;
GLuint shineDamperID;
GLuint reflectivityID;
GLuint modelTextureID;
};
}