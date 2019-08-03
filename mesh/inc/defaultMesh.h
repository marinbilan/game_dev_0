#pragma once
#include "meshIf.h"


namespace Mesh
{
class DefaultMesh : public MeshIf
{
public:
	DefaultMesh(const std::string& name);

	~DefaultMesh();

	const std::string& getName()
	{
		return m_name;
	}

	void preInit();
	void postInit();

	// Get

	void render(const glm::mat4& modelMatrix, 
		const GPUObject::Mesh modelMesh, 
		const GPUObject::TextureStructure textureStruct, 
		const std::shared_ptr<Camera::CameraIf>& camera,
		const std::shared_ptr<Light::LightIf>& light);

	void cmdPrompt(const std::string& arg0);

private:
	// Set
	void setShaderIDs();

std::string m_name;

std::shared_ptr<Shader::DefaultShader> m_defaultShader;


// GET this data from shader
GLuint m_defaultShaderID;
//
// VERTEX SHADER
// GLuint m_projectionMatrixID; // In shader defined
GLuint m_viewMatrixID;
GLuint m_viewMatrixInvID;
GLuint m_modelMatrixID;

GLuint m_lightPositionID;
GLuint m_planeID;

// FRAGMENT SHADER
GLuint m_lightColourID;
GLuint m_shineDamperID;
GLuint m_reflectivityID;

GLuint m_modelTextureID;
};
} // End of namespace