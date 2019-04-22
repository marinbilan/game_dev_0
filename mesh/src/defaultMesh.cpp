#include "defaultMesh.h"

#include "error.h"
#include "factory.h"


Mesh::DefaultMesh::DefaultMesh(Common::Error& err, const std::string& name) : m_name(name)
{
	std::cout << "DefaultMesh created!" << std::endl;
}


Mesh::DefaultMesh::~DefaultMesh()
{
	std::cout << "DefaultMesh destructor called!" << std::endl;
}


void Mesh::DefaultMesh::setTextureId(GLuint texId)
{
	texture0 = texId;
};


void Mesh::DefaultMesh::render()
{
	glUseProgram(m_shaderIf->getShaderProgramID());

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (const GLvoid*)12); // 3 (x, y, z) * 4 (BYTEs) = 12 (BYTES)
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (const GLvoid*)20); // 3 (x, y, z) * 4 (BYTEs) + 2 (u, v) * 4 (BYTEs) = 20 (BYTES)

	glEnableVertexAttribArray(0); // VERTEXs
	glEnableVertexAttribArray(1); // TEXTURECOORDs
	glEnableVertexAttribArray(2); // NORMALs

	// VERTEX SHADER UNIFORMS
	// Projection matrix updated in shader constructor (Only once)
	/*
	glUniformMatrix4fv(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getViewMatrixID(), 1, GL_FALSE, &m_camera.getViewMatrix()[0][0]);
	m_camera.invertCameraMatrix();
	glUniformMatrix4fv(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getViewMatrixInvID(), 1, GL_FALSE, &m_camera.getInvViewMatrix()[0][0]);
	glUniformMatrix4fv(_staticModel.getVectorOfMeshes()[i].meshVectorShaderIf->getModelMatrixID(), 1, GL_FALSE, &(_staticModel.getModelMatrix()[0][0]));
	*/
	// TODO: Remove from here
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
	// glDrawElements(GL_TRIANGLES, _staticModel.getVectorOfMeshes()[i].numIndices, GL_UNSIGNED_INT, 0);
	//
	glUseProgram(0);
};


void Mesh::DefaultMesh::preInit()
{
	shaderIdsInit();
}


void Mesh::DefaultMesh::postInit()
{
	std::cout << "postInit function called!" << std::endl;
}


void Mesh::DefaultMesh::setShader(const std::shared_ptr<Shader::ShaderIf>& shaderIf)
{
	std::cout << " [Mesh::DefaultMesh::setShader] ... " << std::endl;
	m_shaderIf = shaderIf;

	shaderIdsInit();
}


void Mesh::DefaultMesh::shaderIdsInit()
{
	// shaderProgramID = m_shaderIf->getShaderProgramID();

	// ---- Shader IDs ----
    // VERTEX SHADER
	positionsID = m_shaderIf->getPositionsID();
	std::cout << " ---- positionsID: " << positionsID << '\n';
	textureCoordsID = m_shaderIf->getTextureCoordsID();
	std::cout << " ---- textureCoordsID: " << textureCoordsID << '\n';
	GLuint normalsID = m_shaderIf->getNormalsID();
	std::cout << " ---- normalsID: " << normalsID << '\n';

	projectionMatrixID = m_shaderIf->getProjectionMatrixID();
	std::cout << " ---- projectionMatrixID: " << projectionMatrixID << '\n';
	viewMatrixID = m_shaderIf->getViewMatrixID();
	std::cout << " ---- viewMatrixID: " << viewMatrixID << '\n';
	viewMatrixInvID = m_shaderIf->getViewMatrixInvID();
	std::cout << " ---- viewMatrixInvID: " << viewMatrixInvID << '\n';
	modelMatrixID = m_shaderIf->getModelMatrixID();
	std::cout << " ---- modelMatrixID: " << modelMatrixID << '\n';

	lightPositionID = m_shaderIf->getLightPositionID();
	std::cout << " ---- lightPositionID: " << lightPositionID << '\n';
	planeID = m_shaderIf->getPlaneID();
	std::cout << " ---- planeID: " << planeID << '\n';

	// FRAGMENT SHADER
	lightColourID = m_shaderIf->getLightColorID();
	std::cout << " ---- lightColourID: " << lightColourID << '\n';
	shineDamperID = m_shaderIf->getShineDamperID();
	std::cout << " ---- shineDamperID: " << shineDamperID << '\n';
	reflectivityID = m_shaderIf->getReflectivityID();
	std::cout << " ---- reflectivityID: " << reflectivityID << '\n';
	modelTextureID = m_shaderIf->getModelTextureID();
	std::cout << " ---- modelTextureID: " << modelTextureID << '\n';

}


void Mesh::DefaultMesh::cmdPrompt(const std::string& arg0)
{
	std::cout << "cmdPrompt object: " << m_name << " called with arg: " << arg0 << std::endl;
}
