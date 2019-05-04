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
	// Set shaders Ids
	shaderIdsInit();
}


void Mesh::DefaultMesh::postInit()
{
	std::cout << "Mesh::DefaultMesh::postInit(...) called!" << '\n';
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

	glUseProgram(m_shaderIf->getShaderProgramID());

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (const GLvoid*)12); // 3 (x, y, z) * 4 (BYTEs) = 12 (BYTES)
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (const GLvoid*)20); // 3 (x, y, z) * 4 (BYTEs) + 2 (u, v) * 4 (BYTEs) = 20 (BYTES)

	glEnableVertexAttribArray(0); // VERTEXs
	glEnableVertexAttribArray(1); // TEXTURECOORDs
	glEnableVertexAttribArray(2); // NORMALs

	// VERTEX SHADER UNIFORMS
	// Projection matrix updated in shader constructor (Only once)
	glUniformMatrix4fv(m_shaderIf->getViewMatrixID(), 1, GL_FALSE, &m_cameraIf->getViewMatrix()[0][0]);
	m_cameraIf->invertCameraMatrix();
	glUniformMatrix4fv(m_shaderIf->getViewMatrixInvID(), 1, GL_FALSE, &m_cameraIf->getInvViewMatrix()[0][0]);

	glUniformMatrix4fv(m_shaderIf->getModelMatrixID(), 1, GL_FALSE, &modelMatrix[0][0]);
	
	glm::vec3 lightPositionModelPTN(385.0f, 77.0f, 385.0f);
	glm::vec3 lightColorModelPTN(1.0f, 1.0f, 1.0f);

	glUniform3f(lightPositionID, lightPositionModelPTN[0], lightPositionModelPTN[1], lightPositionModelPTN[2]);
	glm::vec4 planeModelPTN(0.0f, -1.0f, 0.0f, 100000.0f);
	glUniform4f(planeID, planeModelPTN[0], planeModelPTN[1], planeModelPTN[2], planeModelPTN[3]);
	// FRAGMENT SHADER UNIFORMS
	glUniform3f(lightColourID, lightColorModelPTN[0], lightColorModelPTN[1], lightColorModelPTN[2]);
	glUniform1f(shineDamperID, 5.0f);
	glUniform1f(reflectivityID, 0.1f);

	glUniform1i(modelTextureID, 0);

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


void Mesh::DefaultMesh::setShader(const std::shared_ptr<Shader::ShaderIf>& shaderIf)
{
	m_shaderIf = shaderIf;

	shaderIdsInit();
}


void Mesh::DefaultMesh::setCamera(const std::shared_ptr<Camera::CameraIf>& cameraIf)
{
	m_cameraIf = cameraIf;

}


void Mesh::DefaultMesh::shaderIdsInit()
{
    // VERTEX SHADER
	positionsID = m_shaderIf->getPositionsID();
	textureCoordsID = m_shaderIf->getTextureCoordsID();
	GLuint normalsID = m_shaderIf->getNormalsID();

	projectionMatrixID = m_shaderIf->getProjectionMatrixID();
	viewMatrixID = m_shaderIf->getViewMatrixID();
	viewMatrixInvID = m_shaderIf->getViewMatrixInvID();
	modelMatrixID = m_shaderIf->getModelMatrixID();

	lightPositionID = m_shaderIf->getLightPositionID();
	planeID = m_shaderIf->getPlaneID();

	// FRAGMENT SHADER
	lightColourID = m_shaderIf->getLightColorID();
	shineDamperID = m_shaderIf->getShineDamperID();
	reflectivityID = m_shaderIf->getReflectivityID();
	modelTextureID = m_shaderIf->getModelTextureID();
}


void Mesh::DefaultMesh::cmdPrompt(const std::string& arg0)
{
	std::cout << "cmdPrompt object: " << m_name << " called with arg: " << arg0 << std::endl;
}
