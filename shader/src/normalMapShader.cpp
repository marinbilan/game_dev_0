#include "normalMapShader.h"

#include "factory.h"

Shader::NormalMapShader::NormalMapShader(const std::string& name) : m_name(name)
{
	FACTORY.getLog()->LOGFILE(LOG "NormalMapShader: " + m_name + " created.");
}


Shader::NormalMapShader::NormalMapShader(const std::string& dbPath, const std::string& name) : 
	m_dbPath(dbPath),
	m_name(name)
{
	FACTORY.getLog()->LOGFILE(LOG "NormalMapShader: " + m_name + " created.");

	m_dbPathWithName = m_dbPath + m_name + "_";
	std::cout << " CREATION INSTANCE - m_dbPathWithName: " << m_dbPathWithName << " modelName: " << m_name << '\n';
}


Shader::NormalMapShader::~NormalMapShader()
{
}


// FUNCTIONs
void Shader::NormalMapShader::preInit()
{
	// TODO remove this
	GLfloat projMatrixWidth = 800;
	GLfloat projMatrixHeight = 600;

	m_shaderProgramID = createShader(VertexShaderNormalMapPTNT, FragmentShaderNormalMapPTNT);
	// [ VERTEX SHADER ]
	//   ATTRIBUTEs
	m_positionsID = glGetAttribLocation(m_shaderProgramID, "position");
	m_textureCoordsID = glGetAttribLocation(m_shaderProgramID, "textureCoordinates");
	m_normalsID = glGetAttribLocation(m_shaderProgramID, "normal");
	m_tangentsID = glGetAttribLocation(m_shaderProgramID, "tangent");
	// [ UNIFORMs ]
	m_projectionMatrixID = glGetUniformLocation(m_shaderProgramID, "projectionMatrix");
	m_viewMatrixID = glGetUniformLocation(m_shaderProgramID, "viewMatrix");
	//m_viewMatrixInvID = glGetUniformLocation(m_shaderProgramID, "viewMatrixInv");
	m_modelMatrixID = glGetUniformLocation(m_shaderProgramID, "transformationMatrix");

	m_lightPositionEyeSpaceID = glGetUniformLocation(m_shaderProgramID, "lightPositionEyeSpace");
	// [ FRAGMENT SHADER ]
	//   UNIFORMs
	m_lightColourID = glGetUniformLocation(m_shaderProgramID, "lightColour");
	m_shineDamperID = glGetUniformLocation(m_shaderProgramID, "shineDamper");
	m_reflectivityID = glGetUniformLocation(m_shaderProgramID, "reflectivity");
	m_modelTextureID = glGetUniformLocation(m_shaderProgramID, "modelTexture");
	m_modelNormalMapID = glGetUniformLocation(m_shaderProgramID, "normalMap");
	//
	// Set Projection Matrix
	// 
	m_projectionMatrix = glm::perspective(glm::radians(60.0f), projMatrixWidth / projMatrixHeight, 0.1f, 1000.f);
	glUseProgram(m_shaderProgramID);
	glUniformMatrix4fv(m_projectionMatrixID, 1, GL_FALSE, &m_projectionMatrix[0][0]);
	glUseProgram(0);
}


void Shader::NormalMapShader::postInit()
{
}


// ========================================================================================
// NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION
// ========================================================================================
void Shader::NormalMapShader::preInitialization()
{
}


void Shader::NormalMapShader::postInitialization()
{
}


void Shader::NormalMapShader::render(const glm::mat4& modelMatrix,
	const GPUObject::MeshStructure modelMesh,
	const GPUObject::TextureStructure textureStruct,
	const std::shared_ptr<Camera::CameraIf>& camera,
	const std::shared_ptr<Light::LightIf>& light)
{
	// ---- ModelGPUObject StructOfMeshe for each mesh ----
	glBindVertexArray(modelMesh.m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, modelMesh.m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelMesh.m_IBO);
	// ---- ----

	// ---- Shader ----
	glUseProgram(m_shaderProgramID);
	// ---- ----

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (const GLvoid*)12); // 3 (x, y, z) * 4 (BYTEs) = 12 (BYTES)
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (const GLvoid*)20); // 3 (x, y, z) * 4 (BYTEs) + 2 (u, v) * 4 (BYTEs) = 20 (BYTES)
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 32, (const GLvoid*)32); // Tangent

	glEnableVertexAttribArray(0); // VERTEXs
	glEnableVertexAttribArray(1); // TEXTURECOORDs
	glEnableVertexAttribArray(2); // NORMALs
	glEnableVertexAttribArray(3); // TANGENTs

	// [ VERTEX SHADER UNIFORMS ]
	// Projection matrix updated in shader constructor (Only once)
	// ---- Camera ----
	glUniformMatrix4fv(m_viewMatrixID, 1, GL_FALSE, &camera->getViewMatrix()[0][0]);
	// ---- ----

	// ---- Model Matrix ----
	glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
	// ---- ----

	// ---- Light ----
	glm::vec3 lightPositionEyeSpace(395.0f, 7.0f, 385.0f);
	glUniform3f(m_lightPositionEyeSpaceID, lightPositionEyeSpace[0], lightPositionEyeSpace[1], lightPositionEyeSpace[2]);
	// ---- ----

	// [ FRAGMENT SHADER UNIFORMS ]
	// ---- Light ----
	glm::vec3 lightColorModelPTN(1.0f, 1.0f, 1.0f);
	glUniform3f(m_lightColourID, lightColorModelPTN[0], lightColorModelPTN[1], lightColorModelPTN[2]);
	// ---- ----

	// // ---- TextureGPUObject StructOfTexture for each mesh ----
	glUniform1f(m_shineDamperID, 15.0f);
	glUniform1f(m_reflectivityID, 0.2f);

	// Texture
	glUniform1i(m_modelTextureID, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureStruct.m_textureId);

	// NormalMap Texture
	glUniform1i(m_modelNormalMapID, 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureStruct.m_textureNormalMapId);

	// ---- RENDER MESH ----
	// ---- ModelGPUObject StructOfMeshe for each mesh ----
	glDrawElements(GL_TRIANGLES, modelMesh.m_NumOfInds, GL_UNSIGNED_INT, 0);
	// ---- ----

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);

	glBindVertexArray(0);

	glUseProgram(0);
};


// OPERATORs
void Shader::NormalMapShader::printINFO()
{
	std::cout << *this;
}


void Shader::NormalMapShader::cmdPrompt(const std::string& arg0)
{
	std::cout << "cmdPrompt object: " << m_name << " called with arg: " << arg0 << std::endl;
}