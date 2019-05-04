#pragma once
#include "meshIf.h"

#include "error.h"


namespace Mesh
{
class DefaultMesh : public MeshIf
{
public:
	DefaultMesh(Common::Error& err, const std::string& name);

	~DefaultMesh();

	const std::string& getName()
	{
		return m_name;
	}

	void preInit();
	void postInit();

	// Get

	// Set
	void setShader(const std::shared_ptr<Shader::ShaderIf>& shaderIf);

	void setVBO(GLuint VBO);
	void setIBO(GLuint IBO);
	void setNumOfInd(GLuint numOfInd);

	void setCamera(const std::shared_ptr<Camera::CameraIf>& cameraIf);

	virtual void setTextureId(GLuint texId);

	void render(const glm::mat4& modelMatrix);

	void cmdPrompt(const std::string& arg0);

	// TODO: Remove
	void shaderIdsInit();

private:
std::string m_name;

// TODO: Encapsulate this
GLuint m_VBO;
GLuint m_IBO;
GLuint m_numOfInd;

std::shared_ptr<Shader::ShaderIf> m_shaderIf;
std::shared_ptr<Camera::CameraIf> m_cameraIf;

// Lights ... 
GLuint texture0;

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