#include "defaultShader.h"

#include "error.h"


Shader::DefaultShader::DefaultShader(Common::Error& err, const std::string& name) : m_name(name)
{
	std::cout << "DefaultShader created!" << std::endl;
}


Shader::DefaultShader::~DefaultShader()
{
	std::cout << "DefaultShader destructor called!" << std::endl;
}


Shader::DefaultShader::DefaultShader(GLfloat projMatrixWidth, GLfloat projMatrixHeight)
{
	shaderName = "ShaderPTN0"; // Hardcoded shader name
	shaderProgramID = createShader(VertexShaderPTN, FragmentShaderPTN);
	// [ VERTEX SHADER ]
	//   ATTRIBUTEs
	positionsID = glGetAttribLocation(shaderProgramID, "position");
	textureCoordsID = glGetAttribLocation(shaderProgramID, "textureCoordinates");
	normalsID = glGetAttribLocation(shaderProgramID, "normal");
	// [ UNIFORMs ]
	projectionMatrixID = glGetUniformLocation(shaderProgramID, "projectionMatrix");
	viewMatrixID = glGetUniformLocation(shaderProgramID, "viewMatrix");
	viewMatrixInvID = glGetUniformLocation(shaderProgramID, "viewMatrixInv");
	modelMatrixID = glGetUniformLocation(shaderProgramID, "transformationMatrix");

	lightPositionID = glGetUniformLocation(shaderProgramID, "lightPosition");
	planeID = glGetUniformLocation(shaderProgramID, "plane");
	// [ FRAGMENT SHADER ]
	//   UNIFORMs
	lightColourID = glGetUniformLocation(shaderProgramID, "lightColour");
	shineDamperID = glGetUniformLocation(shaderProgramID, "shineDamper");
	reflectivityID = glGetUniformLocation(shaderProgramID, "reflectivity");
	modelTextureID = glGetUniformLocation(shaderProgramID, "modelTexture");
	//
	// Set Projection Matrix
	// 
	// projectionMatrix = glm::perspective(glm::radians(60.0f), projMatrixWidth / projMatrixHeight, 0.1f, 1000.f);
	glUseProgram(shaderProgramID);
	// glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUseProgram(0);

	std::cout << "ShaderPTN0 created!" << std::endl;
}

// FUNCTIONs
std::string Shader::DefaultShader::getShaderName()
{
	return shaderName;
}

GLuint const Shader::DefaultShader::getShaderProgramID() const
{
	return shaderProgramID;
}

GLuint const Shader::DefaultShader::getPositionsID() const
{
	return positionsID;
}

GLuint const Shader::DefaultShader::getTextureCoordsID() const
{
	return textureCoordsID;
}

GLuint const Shader::DefaultShader::getNormalsID() const
{
	return normalsID;
}

GLuint const Shader::DefaultShader::getProjectionMatrixID() const
{
	return projectionMatrixID;
}

GLuint const Shader::DefaultShader::getViewMatrixID() const
{
	return viewMatrixID;
}

GLuint const Shader::DefaultShader::getViewMatrixInvID() const
{
	return viewMatrixInvID;
}

GLuint const Shader::DefaultShader::getModelMatrixID() const
{
	return modelMatrixID;
}

GLuint const Shader::DefaultShader::getLightPositionID() const
{
	return lightPositionID;
}

GLuint const Shader::DefaultShader::getPlaneID() const
{
	return planeID;
}
// FRAGMENT SHADER
GLuint const Shader::DefaultShader::getLightColorID() const
{
	return lightColourID;
}

GLuint const Shader::DefaultShader::getShineDamperID() const
{
	return shineDamperID;
}

GLuint const Shader::DefaultShader::getReflectivityID() const
{
	return reflectivityID;
}

GLuint const Shader::DefaultShader::getModelTextureID() const
{
	return modelTextureID;
}
// OPERATORs
void Shader::DefaultShader::printINFO()
{
	std::cout << *this;
}


int Shader::DefaultShader::getId()
{
	return 11;
}


void Shader::DefaultShader::preInit()
{

}


void Shader::DefaultShader::postInit()
{
	std::cout << "postInit function called!" << std::endl;
}


void Shader::DefaultShader::cmdPrompt(const std::string& arg0)
{
	std::cout << "cmdPrompt object: " << m_name << " called with arg: " << arg0 << std::endl;
}