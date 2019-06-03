#include "defaultMesh.h"

#include "factory.h"


Mesh::DefaultMesh::DefaultMesh(Common::Error& err, const std::string& name) : m_name(name)
{
	std::cout << "Mesh::DefaultMesh::DefaultMesh(...) constructor called!" << '\n';
}


Mesh::DefaultMesh::~DefaultMesh()
{
	std::cout << "Mesh::DefaultMesh::~DefaultMesh(...) destructor called!" << '\n';
}


void Mesh::DefaultMesh::preInit()
{
	std::cout << "Mesh::DefaultMesh::preInit(...) called!" << '\n';

	std::string shaderDbName;
	FACTORY.getDatabase()->getStringFromDB(m_name, "shader", shaderDbName);

	//std::cout << " --------------- stringFromDb: " << shaderDbName << "\n";

	m_defaultShader = std::dynamic_pointer_cast<Shader::DefaultShader>( FACTORY.getShaderIf(shaderDbName) ); // downcast
	//std::cout << " --------------- m_defaultShader: " << m_defaultShader->getName() << "\n";

	setShader();
}


void Mesh::DefaultMesh::postInit()
{
	// std::cout << " **************************** Mesh::DefaultMesh::postInit(...) called!" << '\n';

	std::string cameraDbName;
	FACTORY.getDatabase()->getStringFromDB(m_name, "camera", cameraDbName);

	// std::cout << m_name << " --------------- stringFromDb: " << cameraDbName << "\n";

	m_cameraIf = FACTORY.getCameraIf(cameraDbName);

	// Combine objects here
}

/*
void Mesh::DefaultMesh::setShader(const std::shared_ptr<Shader::ShaderIf>& shaderIf)
{
	m_shaderIf = shaderIf;
	m_defaultShader = std::dynamic_pointer_cast<Shader::DefaultShader>(shaderIf);

	// ShaderId
	m_defaultShaderID = m_defaultShader->shaderProgramID;

	// VERTEX SHADER
	// m_projectionMatrixID = m_shaderIf->getProjectionMatrixID();
	m_viewMatrixID = m_defaultShader->viewMatrixID;
	m_viewMatrixInvID = m_defaultShader->viewMatrixInvID;
	m_modelMatrixID = m_defaultShader->modelMatrixID;

	m_lightPositionID = m_defaultShader->lightPositionID;
	m_planeID = m_defaultShader->planeID;

	// FRAGMENT SHADER
	m_lightColourID = m_defaultShader->lightColourID;
	m_shineDamperID = m_defaultShader->shineDamperID;
	m_reflectivityID = m_defaultShader->reflectivityID;
	m_modelTextureID = m_defaultShader->modelTextureID;
}
*/

void Mesh::DefaultMesh::setShader()
{
	// ShaderId
	m_defaultShaderID = m_defaultShader->shaderProgramID;

	// VERTEX SHADER
	// m_projectionMatrixID = m_shaderIf->getProjectionMatrixID();
	m_viewMatrixID = m_defaultShader->viewMatrixID;
	m_viewMatrixInvID = m_defaultShader->viewMatrixInvID;
	m_modelMatrixID = m_defaultShader->modelMatrixID;

	m_lightPositionID = m_defaultShader->lightPositionID;
	m_planeID = m_defaultShader->planeID;

	// FRAGMENT SHADER
	m_lightColourID = m_defaultShader->lightColourID;
	m_shineDamperID = m_defaultShader->shineDamperID;
	m_reflectivityID = m_defaultShader->reflectivityID;
	m_modelTextureID = m_defaultShader->modelTextureID;
}


void Mesh::DefaultMesh::setCamera(const std::shared_ptr<Camera::CameraIf>& cameraIf)
{
	m_cameraIf = cameraIf;

}


void Mesh::DefaultMesh::setTextureId(GLuint texId)
{
	texture0 = texId;
};


void Mesh::DefaultMesh::setVBO(GLuint VBO)
{
	m_VBO = VBO;
}


void Mesh::DefaultMesh::setIBO(GLuint IBO)
{
	m_IBO = IBO;
}


void Mesh::DefaultMesh::setNumOfInd(GLuint numOfInd)
{
	m_numOfInd = numOfInd;
}


void Mesh::DefaultMesh::render(const glm::mat4& modelMatrix)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	glUseProgram(m_defaultShaderID);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (const GLvoid*)12); // 3 (x, y, z) * 4 (BYTEs) = 12 (BYTES)
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (const GLvoid*)20); // 3 (x, y, z) * 4 (BYTEs) + 2 (u, v) * 4 (BYTEs) = 20 (BYTES)

	glEnableVertexAttribArray(0); // VERTEXs
	glEnableVertexAttribArray(1); // TEXTURECOORDs
	glEnableVertexAttribArray(2); // NORMALs

	// VERTEX SHADER UNIFORMS
	// Projection matrix updated in shader constructor (Only once)
	glUniformMatrix4fv(m_viewMatrixID, 1, GL_FALSE, &m_cameraIf->getViewMatrix()[0][0]);
	m_cameraIf->invertCameraMatrix();
	glUniformMatrix4fv(m_viewMatrixInvID, 1, GL_FALSE, &m_cameraIf->getInvViewMatrix()[0][0]);
	glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
	
	glm::vec3 lightPositionModelPTN(385.0f, 77.0f, 385.0f);
	glm::vec3 lightColorModelPTN(1.0f, 1.0f, 1.0f);

	glUniform3f(m_lightPositionID, lightPositionModelPTN[0], lightPositionModelPTN[1], lightPositionModelPTN[2]);
	glm::vec4 planeModelPTN(0.0f, -1.0f, 0.0f, 100000.0f);
	glUniform4f(m_planeID, planeModelPTN[0], planeModelPTN[1], planeModelPTN[2], planeModelPTN[3]);
	// FRAGMENT SHADER UNIFORMS
	glUniform3f(m_lightColourID, lightColorModelPTN[0], lightColorModelPTN[1], lightColorModelPTN[2]);
	glUniform1f(m_shineDamperID, 5.0f);
	glUniform1f(m_reflectivityID, 0.1f);

	glUniform1i(m_modelTextureID, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	// RENDER MESH
	glDrawElements(GL_TRIANGLES, m_numOfInd, GL_UNSIGNED_INT, 0);
	//
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindVertexArray(0);

	glUseProgram(0);
};


void Mesh::DefaultMesh::cmdPrompt(const std::string& arg0)
{
	std::cout << "cmdPrompt object: " << m_name << " called with arg: " << arg0 << std::endl;
}
