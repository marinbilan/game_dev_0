#include "defaultShader.h"


Shader::DefaultShader::DefaultShader(Common::Error& err, const std::string& name) : m_name(name)
{
	std::cout << "DefaultShader created!" << std::endl;

	// TODO remove this
	GLfloat projMatrixWidth = 800;
	GLfloat projMatrixHeight = 600;

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
	projectionMatrix = glm::perspective(glm::radians(60.0f), projMatrixWidth / projMatrixHeight, 0.1f, 1000.f);
	glUseProgram(shaderProgramID);
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUseProgram(0);

	std::cout << "ShaderPTN0 created!" << std::endl;
}


Shader::DefaultShader::~DefaultShader()
{
	std::cout << "DefaultShader destructor called!" << std::endl;
}


// FUNCTIONs
void Shader::DefaultShader::preInit()
{

}


void Shader::DefaultShader::postInit()
{
	std::cout << "postInit function called!" << std::endl;
}


// OPERATORs
void Shader::DefaultShader::printINFO()
{
	std::cout << *this;
}


void Shader::DefaultShader::cmdPrompt(const std::string& arg0)
{
	std::cout << "cmdPrompt object: " << m_name << " called with arg: " << arg0 << std::endl;
}