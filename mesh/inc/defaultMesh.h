#pragma once
#include "meshIf.h"

#include "error.h"


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

	// Set
	void setShader();

	// TODO: remove this
	virtual void setTextureId(GLuint texId);

	// Get
	void render(const glm::mat4& modelMatrix, GLuint VAO, GLuint VBO, GLuint IBO, GLuint numOfInds, const GPUObject::TextureStructure textureStruct);
	void render(const glm::mat4& modelMatrix, const GPUObject::Mesh modelMesh, const GPUObject::TextureStructure textureStruct);

	void render(const glm::mat4& modelMatrix, GLuint VBO, GLuint IBO, GLuint numOfInds);

	void cmdPrompt(const std::string& arg0);

private:
std::string m_name;

std::shared_ptr<Camera::CameraIf> m_cameraIf;
std::shared_ptr<Shader::DefaultShader> m_defaultShader;

// Lights ... 

// TODO: remove from here
GLuint texture0;

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