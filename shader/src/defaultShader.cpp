#include "defaultShader.h"

#include "factory.h"

Shader::DefaultShader::DefaultShader(const std::string& name) : m_name(name)
{
}


Shader::DefaultShader::DefaultShader(const std::string& dbPath, const std::string& name) : 
	m_dbPath(dbPath),
	m_name(name)
{
	m_dbPathWithName = m_dbPath + m_name + "_";

	std::string instName = m_dbPathWithName + m_name;
	FACTORY.getLog()->LOGFILE(LOG "DefaultShader: " + m_name + " created.");
}


Shader::DefaultShader::~DefaultShader()
{
}


// FUNCTIONs
void Shader::DefaultShader::preInit()
{
	// TODO remove this
	GLfloat projMatrixWidth = 800;
	GLfloat projMatrixHeight = 600;

	m_shaderProgramID = createShader(VertexShaderPTN, FragmentShaderPTN);
	// [ VERTEX SHADER ]
	//   ATTRIBUTEs
	m_positionsID = glGetAttribLocation(m_shaderProgramID, "position");
	m_textureCoordsID = glGetAttribLocation(m_shaderProgramID, "textureCoordinates");
	m_normalsID = glGetAttribLocation(m_shaderProgramID, "normal");
	// [ UNIFORMs ]
	m_projectionMatrixID = glGetUniformLocation(m_shaderProgramID, "projectionMatrix");
	m_viewMatrixID = glGetUniformLocation(m_shaderProgramID, "viewMatrix");
	m_viewMatrixInvID = glGetUniformLocation(m_shaderProgramID, "viewMatrixInv");
	m_modelMatrixID = glGetUniformLocation(m_shaderProgramID, "transformationMatrix");

	m_lightPositionID = glGetUniformLocation(m_shaderProgramID, "lightPosition");
	m_planeID = glGetUniformLocation(m_shaderProgramID, "plane");
	// [ FRAGMENT SHADER ]
	//   UNIFORMs
	m_lightColourID = glGetUniformLocation(m_shaderProgramID, "lightColour");
	m_shineDamperID = glGetUniformLocation(m_shaderProgramID, "shineDamper");
	m_reflectivityID = glGetUniformLocation(m_shaderProgramID, "reflectivity");
	m_modelTextureID = glGetUniformLocation(m_shaderProgramID, "modelTexture");
	//
	// Set Projection Matrix
	// 
	m_projectionMatrix = glm::perspective(glm::radians(60.0f), projMatrixWidth / projMatrixHeight, 0.1f, 1000.f);
	glUseProgram(m_shaderProgramID);
	glUniformMatrix4fv(m_projectionMatrixID, 1, GL_FALSE, &m_projectionMatrix[0][0]);
	glUseProgram(0);
}


void Shader::DefaultShader::postInit()
{
}


// ========================================================================================
// NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION
// ========================================================================================
void Shader::DefaultShader::preInitialization()
{
	// TODO remove this
	GLfloat projMatrixWidth = 800;
	GLfloat projMatrixHeight = 600;

	m_shaderProgramID = createShader(VertexShaderPTN, FragmentShaderPTN);
	// [ VERTEX SHADER ]
	//   ATTRIBUTEs
	m_positionsID = glGetAttribLocation(m_shaderProgramID, "position");
	m_textureCoordsID = glGetAttribLocation(m_shaderProgramID, "textureCoordinates");
	m_normalsID = glGetAttribLocation(m_shaderProgramID, "normal");
	// [ UNIFORMs ]
	m_projectionMatrixID = glGetUniformLocation(m_shaderProgramID, "projectionMatrix");
	m_viewMatrixID = glGetUniformLocation(m_shaderProgramID, "viewMatrix");
	m_viewMatrixInvID = glGetUniformLocation(m_shaderProgramID, "viewMatrixInv");
	m_modelMatrixID = glGetUniformLocation(m_shaderProgramID, "transformationMatrix");

	m_lightPositionID = glGetUniformLocation(m_shaderProgramID, "lightPosition");
	m_planeID = glGetUniformLocation(m_shaderProgramID, "plane");
	// [ FRAGMENT SHADER ]
	//   UNIFORMs
	m_lightColourID = glGetUniformLocation(m_shaderProgramID, "lightColour");
	m_shineDamperID = glGetUniformLocation(m_shaderProgramID, "shineDamper");
	m_reflectivityID = glGetUniformLocation(m_shaderProgramID, "reflectivity");
	m_modelTextureID = glGetUniformLocation(m_shaderProgramID, "modelTexture");
	//
	// Set Projection Matrix
	// 
	m_projectionMatrix = glm::perspective(glm::radians(60.0f), projMatrixWidth / projMatrixHeight, 0.1f, 1000.f);
	glUseProgram(m_shaderProgramID);
	glUniformMatrix4fv(m_projectionMatrixID, 1, GL_FALSE, &m_projectionMatrix[0][0]);
	glUseProgram(0);
}


void Shader::DefaultShader::postInitialization()
{
}


void Shader::DefaultShader::render(const glm::mat4& modelMatrix,
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

	glEnableVertexAttribArray(0); // VERTEXs
	glEnableVertexAttribArray(1); // TEXTURECOORDs
	glEnableVertexAttribArray(2); // NORMALs

	// [ VERTEX SHADER UNIFORMS ]
	// Projection matrix updated in shader constructor (Only once)
	// ---- Camera ----
	glUniformMatrix4fv(m_viewMatrixID, 1, GL_FALSE, &camera->getViewMatrix()[0][0]);
	camera->invertCameraMatrix();
	glUniformMatrix4fv(m_viewMatrixInvID, 1, GL_FALSE, &camera->getInvViewMatrix()[0][0]);
	// ---- ----

	// ---- Model Matrix ----
	glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
	// ---- ----

	// ---- Light ----
	glUniform3f(m_lightPositionID, light->getLightPosition()[0], light->getLightPosition()[1], light->getLightPosition()[2]);
	// ---- ----

	glm::vec4 planeModelPTN(0.0f, -1.0f, 0.0f, 100000.0f);
	glUniform4f(m_planeID, planeModelPTN[0], planeModelPTN[1], planeModelPTN[2], planeModelPTN[3]);

	// [ FRAGMENT SHADER UNIFORMS ]
	// ---- Light ----
	glUniform3f(m_lightColourID, light->getLightColors()[0], light->getLightColors()[1], light->getLightColors()[2]);
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


// OPERATORs
void Shader::DefaultShader::printINFO()
{
	std::cout << *this;
}


void Shader::DefaultShader::cmdPrompt(const std::string& arg0)
{
	std::cout << "cmdPrompt object: " << m_name << " called with arg: " << arg0 << std::endl;
}