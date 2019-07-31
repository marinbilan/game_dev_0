#include "defaultMesh.h"

#include "factory.h"


Mesh::DefaultMesh::DefaultMesh(const std::string& name) : m_name(name)
{
}


Mesh::DefaultMesh::~DefaultMesh()
{
}


void Mesh::DefaultMesh::preInit()
{
	std::string shaderDbName;
	FACTORY.getDatabase()->getStringFromDB(m_name, "shader", shaderDbName);

	m_defaultShader = std::dynamic_pointer_cast<Shader::DefaultShader>( FACTORY.getShaderIf(shaderDbName) ); // downcast

	setShader();
}


void Mesh::DefaultMesh::postInit()
{
	std::string cameraDbName;
	FACTORY.getDatabase()->getStringFromDB(m_name, "camera", cameraDbName);

	m_cameraIf = FACTORY.getCameraIf(cameraDbName);

	// Combine objects here
	std::string textureName;
	FACTORY.getDatabase()->getRest(m_name, "texture", textureName);

	// TODO: Remove from here - set this in render method during runtime
	texture0 = FACTORY.getGPUObjectIf(textureName)->getTextureID();
}


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


void Mesh::DefaultMesh::setTextureId(GLuint texId)
{
	texture0 = texId;
};


void Mesh::DefaultMesh::render(const glm::mat4& modelMatrix, GLuint VAO, GLuint VBO, GLuint IBO, GLuint numOfInds, const GPUObject::TextureStructure textureStruct)
{
	// ---- ModelGPUObject StructOfMeshe for each mesh ----
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (const GLvoid*)12); // 3 (x, y, z) * 4 (BYTEs) = 12 (BYTES)
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (const GLvoid*)20); // 3 (x, y, z) * 4 (BYTEs) + 2 (u, v) * 4 (BYTEs) = 20 (BYTES)

	glEnableVertexAttribArray(0); // VERTEXs
	glEnableVertexAttribArray(1); // TEXTURECOORDs
	glEnableVertexAttribArray(2); // NORMALs
	// ---- ----

	// ---- Shader ----
	glUseProgram(m_defaultShaderID);
	// ---- ----

	// [ VERTEX SHADER UNIFORMS ]
	// Projection matrix updated in shader constructor (Only once)

	// ---- Camera ----
	glUniformMatrix4fv(m_viewMatrixID, 1, GL_FALSE, &m_cameraIf->getViewMatrix()[0][0]);
	m_cameraIf->invertCameraMatrix();
	glUniformMatrix4fv(m_viewMatrixInvID, 1, GL_FALSE, &m_cameraIf->getInvViewMatrix()[0][0]);
	// ---- ----

	// ---- Model Matrix ----
	glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
	// ---- ----

	// ---- Light ----
	glm::vec3 lightPositionModelPTN(385.0f, 77.0f, 385.0f);
	glm::vec3 lightColorModelPTN(1.0f, 1.0f, 1.0f);
	glUniform3f(m_lightPositionID, lightPositionModelPTN[0], lightPositionModelPTN[1], lightPositionModelPTN[2]);
	// ---- ----

	glm::vec4 planeModelPTN(0.0f, -1.0f, 0.0f, 100000.0f);
	glUniform4f(m_planeID, planeModelPTN[0], planeModelPTN[1], planeModelPTN[2], planeModelPTN[3]);

	// [ FRAGMENT SHADER UNIFORMS ]
	// ---- Light ----
	glUniform3f(m_lightColourID, lightColorModelPTN[0], lightColorModelPTN[1], lightColorModelPTN[2]);
	// ---- ----

	// // ---- TextureGPUObject StructOfTexture for each mesh ----
	glUniform1f(m_shineDamperID, textureStruct.m_shineDamper);
    glUniform1f(m_reflectivityID, textureStruct.m_reflectivity);

	glUniform1i(m_modelTextureID, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureStruct.m_textureId);

	// ---- RENDER MESH ----
	// ---- ModelGPUObject StructOfMeshe for each mesh ----
	glDrawElements(GL_TRIANGLES, numOfInds, GL_UNSIGNED_INT, 0);
	// ---- ----

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindVertexArray(0);

	glUseProgram(0);
};


void Mesh::DefaultMesh::render(const glm::mat4& modelMatrix, GLuint VBO, GLuint IBO, GLuint numOfInds)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

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
	glDrawElements(GL_TRIANGLES, numOfInds, GL_UNSIGNED_INT, 0);
	//
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindVertexArray(0);

	glUseProgram(0);
};


void Mesh::DefaultMesh::render(const glm::mat4& modelMatrix, const GPUObject::Mesh modelMesh, const GPUObject::TextureStructure textureStruct)
{
	// ---- ModelGPUObject StructOfMeshe for each mesh ----
	glBindVertexArray(modelMesh.m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, modelMesh.m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelMesh.m_IBO);
	// ---- ----

	// ---- Shader ----
	glUseProgram(m_defaultShaderID);
	// ---- ----

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (const GLvoid*)12); // 3 (x, y, z) * 4 (BYTEs) = 12 (BYTES)
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (const GLvoid*)20); // 3 (x, y, z) * 4 (BYTEs) + 2 (u, v) * 4 (BYTEs) = 20 (BYTES)

	glEnableVertexAttribArray(0); // VERTEXs
	glEnableVertexAttribArray(1); // TEXTURECOORDs
	glEnableVertexAttribArray(2); // NORMALs

	// [ VERTEX SHADER UNIFORMS ]
	// Projection matrix updated in shader constructor (Only once)

	// ---- Camera ----
	glUniformMatrix4fv(m_viewMatrixID, 1, GL_FALSE, &m_cameraIf->getViewMatrix()[0][0]);
	m_cameraIf->invertCameraMatrix();
	glUniformMatrix4fv(m_viewMatrixInvID, 1, GL_FALSE, &m_cameraIf->getInvViewMatrix()[0][0]);
	// ---- ----

	// ---- Model Matrix ----
	glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
	// ---- ----

	// ---- Light ----
	glm::vec3 lightPositionModelPTN(385.0f, 77.0f, 385.0f);
	glm::vec3 lightColorModelPTN(1.0f, 1.0f, 1.0f);
	glUniform3f(m_lightPositionID, lightPositionModelPTN[0], lightPositionModelPTN[1], lightPositionModelPTN[2]);
	// ---- ----

	glm::vec4 planeModelPTN(0.0f, -1.0f, 0.0f, 100000.0f);
	glUniform4f(m_planeID, planeModelPTN[0], planeModelPTN[1], planeModelPTN[2], planeModelPTN[3]);

	// [ FRAGMENT SHADER UNIFORMS ]
	// ---- Light ----
	glUniform3f(m_lightColourID, lightColorModelPTN[0], lightColorModelPTN[1], lightColorModelPTN[2]);
	// ---- ----

	// // ---- TextureGPUObject StructOfTexture for each mesh ----
	glUniform1f(m_shineDamperID, textureStruct.m_shineDamper);
	glUniform1f(m_reflectivityID, textureStruct.m_reflectivity);

	glUniform1i(m_modelTextureID, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureStruct.m_textureId);

	// ---- RENDER MESH ----
	// ---- ModelGPUObject StructOfMeshe for each mesh ----
	glDrawElements(GL_TRIANGLES, modelMesh.m_NumOfInds, GL_UNSIGNED_INT, 0);
	// ---- ----

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindVertexArray(0);

	glUseProgram(0);
};



void Mesh::DefaultMesh::cmdPrompt(const std::string& arg0)
{
}
