#include "terrainShader.h"

#include "factory.h"


Shader::TerrainShader::TerrainShader(const std::string& name) : m_name(name)
{
	FACTORY.getLog()->LOGFILE(LOG "Terrain: " + m_name + " created.");
}


Shader::TerrainShader::~TerrainShader()
{
}


// FUNCTIONs
void Shader::TerrainShader::preInit()
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


void Shader::TerrainShader::postInit()
{
}


void Shader::TerrainShader::render(const glm::mat4& modelMatrix,
	const GPUObject::MeshStructure modelMesh,
	const GPUObject::TextureStructure textureStruct,
	const std::shared_ptr<Camera::CameraIf>& camera,
	const std::shared_ptr<Light::LightIf>& light)
{

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