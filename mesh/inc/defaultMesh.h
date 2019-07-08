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

	// Get

	// Set
	//void setShader(const std::shared_ptr<Shader::ShaderIf>& shaderIf); // TODO: Remove
	void setShader();

	void setCamera(const std::shared_ptr<Camera::CameraIf>& cameraIf);

	void setVBO(GLuint VBO);
	void setIBO(GLuint IBO);
	void setNumOfInd(GLuint numOfInd);

	virtual void setTextureId(GLuint texId);

	void render(const glm::mat4& modelMatrix);

	void cmdPrompt(const std::string& arg0);

private:
std::string m_name;

// TODO: Encapsulate this
GLuint m_VBO;
GLuint m_IBO;
GLuint m_numOfInd;

std::shared_ptr<Camera::CameraIf> m_cameraIf;

// std::shared_ptr<Shader::ShaderIf>      m_shaderIf;    // TODO: remove
std::shared_ptr<Shader::DefaultShader> m_defaultShader;

// Lights ... 
GLuint texture0;

GLuint m_defaultShaderID;

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