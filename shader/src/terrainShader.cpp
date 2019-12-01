#include "terrainShader.h"

#include "factory.h"


Shader::TerrainShader::TerrainShader(const std::string& dbPath, const std::string& name) : 
	m_dbPath(dbPath),
	m_name(name)
{
	m_dbPathWithName = m_dbPath + m_name + "_";

	std::string instName = m_dbPathWithName + m_name;
	FACTORY.getLog()->LOGFILE(LOG "TerrainShader: " + m_name + " created.");
}


Shader::TerrainShader::~TerrainShader()
{
}


void Shader::TerrainShader::preInitialization()
{
	// TODO remove this
	GLfloat projMatrixWidth = 800;
	GLfloat projMatrixHeight = 600;

	m_shaderProgramID = createShader(vertexShader, fragmentShader);
	// [ VERTEX SHADER ]
	//   ATTRIBUTEs
	m_positionsID = glGetAttribLocation(m_shaderProgramID, "position");
	m_textureCoordsID = glGetAttribLocation(m_shaderProgramID, "textureCoords");
	m_normalsID = glGetAttribLocation(m_shaderProgramID, "normal");
	//   UNIFORMs
	m_projectionMatrixID = glGetUniformLocation(m_shaderProgramID, "projectionMatrix");
	m_viewMatrixID = glGetUniformLocation(m_shaderProgramID, "viewMatrix");
	m_viewMatrixInvID = glGetUniformLocation(m_shaderProgramID, "viewMatrixInv");
	m_modelMatrixID = glGetUniformLocation(m_shaderProgramID, "transformationMatrix");

	m_lightPositionID = glGetUniformLocation(m_shaderProgramID, "lightPosition");
	// [ FRAGMENT SHADER ]
	//   UNIFORMs
	m_backgroundTextureID = glGetUniformLocation(m_shaderProgramID, "backgroundTexture");
	m_rTextureID = glGetUniformLocation(m_shaderProgramID, "rTexture");
	m_gTextureID = glGetUniformLocation(m_shaderProgramID, "gTexture");
	m_bTextureID = glGetUniformLocation(m_shaderProgramID, "bTexture");
	m_blendMapID = glGetUniformLocation(m_shaderProgramID, "blendMap");

	m_lightColorID = glGetUniformLocation(m_shaderProgramID, "lightColor");
	m_shineDamperID = glGetUniformLocation(m_shaderProgramID, "shineDamper");
	m_reflectivityID = glGetUniformLocation(m_shaderProgramID, "reflectivity");

	// Set Projection Matrix
	m_projectionMatrix = glm::perspective(glm::radians(60.0f), projMatrixWidth / projMatrixHeight, 0.1f, 1000.f);
	glUseProgram(m_shaderProgramID);
	glUniformMatrix4fv(m_projectionMatrixID, 1, GL_FALSE, &m_projectionMatrix[0][0]);
	glUseProgram(0);
}


void Shader::TerrainShader::postInitialization()
{
}


void Shader::TerrainShader::render(const glm::mat4& modelMatrix,
	const GPUObject::MeshStructure modelMesh,
	const GPUObject::TextureStructure textureStruct,
	const std::shared_ptr<Camera::CameraIf>& camera,
	const std::shared_ptr<Light::LightIf>& light)
{

};


void Shader::TerrainShader::render(GLuint VAO,
	std::shared_ptr<Camera::CameraIf>& m_cameraIf,
	const std::shared_ptr<Light::LightIf>& light,
	glm::mat4& m_modelMatrix,
	const GPUObject::TextureStructure textureStruct,
	GLuint numInd)
{
	glUseProgram(m_shaderProgramID);
	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0); // VERTEXs
	glEnableVertexAttribArray(1); // TEXTURECOORDs
	glEnableVertexAttribArray(2); // NORMALs

	glUniformMatrix4fv(m_viewMatrixID, 1, GL_FALSE, &m_cameraIf->getViewMatrix()[0][0]);
	m_cameraIf->invertCameraMatrix();
	glUniformMatrix4fv(m_viewMatrixInvID, 1, GL_FALSE, &m_cameraIf->getInvViewMatrix()[0][0]);
	glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &m_modelMatrix[0][0]);

	glUniform3f(m_lightPositionID, light->getLightPosition()[0], light->getLightPosition()[1], light->getLightPosition()[2]);

	// FRAGMENT SHADER
	// TEXTUREs
	glUniform1i(m_backgroundTextureID, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureStruct.m_terrainTexture1Id);

	glUniform1i(m_rTextureID, 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureStruct.m_terrainTexture2Id);

	glUniform1i(m_gTextureID, 2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, textureStruct.m_terrainTexture3Id);

	glUniform1i(m_bTextureID, 3);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, textureStruct.m_terrainTexture4Id);

	glUniform1i(m_blendMapID, 4);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, textureStruct.m_terrainTexture5Id);

	glm::vec3 lightColorTerrain(1.0f, 1.0f, 1.0f);
	glUniform3f(m_lightColorID, lightColorTerrain[0], lightColorTerrain[1], lightColorTerrain[2]);
	glUniform1f(m_shineDamperID, textureStruct.m_shineDamper);
	glUniform1f(m_reflectivityID, textureStruct.m_reflectivity);

	glDrawElements(GL_TRIANGLES, numInd, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
	glUseProgram(0);
};


// OPERATORs
void Shader::TerrainShader::printINFO()
{
	std::cout << "" << std::endl;
	std::cout << "[ SHADER ]" << std::endl;
	std::cout << " Shader Name:              " << m_name << std::endl;
	std::cout << " ShaderProgramID:          " << m_shaderProgramID << std::endl;
	std::cout << "  [ VERTEX SHADER ]" << std::endl;
	std::cout << "     positionsID         = " << m_positionsID << std::endl;
	std::cout << "     textureCoordsID     = " << m_textureCoordsID << std::endl;
	std::cout << "     normalsID           = " << m_normalsID << std::endl;
	std::cout << "      projectionMatrixID = " << m_projectionMatrixID << std::endl;
	std::cout << "      viewMatrixID       = " << m_viewMatrixID << std::endl;
	std::cout << "      viewMatrixInvID    = " << m_viewMatrixInvID << std::endl;
	std::cout << "      modelMatrixID      = " << m_modelMatrixID << std::endl;
	std::cout << "      lightPositionID    = " << m_lightPositionID << std::endl;
	std::cout << "  [ FRAGMENT SHADER ]" << std::endl;
	std::cout << "      backgroundTextureID= " << m_backgroundTextureID << std::endl;
	std::cout << "      rTextureID         = " << m_rTextureID << std::endl;
	std::cout << "      gTextureID         = " << m_gTextureID << std::endl;
	std::cout << "      bTextureID         = " << m_bTextureID << std::endl;
	std::cout << "      blendMapID         = " << m_blendMapID << std::endl;
	std::cout << "      lightColorID       = " << m_lightColorID << std::endl;
	std::cout << "      shineDamperID      = " << m_shineDamperID << std::endl;
	std::cout << "      reflectivityID     = " << m_reflectivityID << std::endl;
	std::cout << "" << std::endl;
}


void Shader::TerrainShader::cmdPrompt(const std::string& arg0)
{
	std::cout << "cmdPrompt object: " << m_name << " called with arg: " << arg0 << std::endl;
}