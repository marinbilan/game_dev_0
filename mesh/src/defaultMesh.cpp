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


void Mesh::DefaultMesh::render()
{
	std::cout << "Mesh::DefaultMesh::render() : " << m_name << std::endl;
	// defaultShaderIf = Common::Factory::getInstance().getShaderIf("smartShader_0");

	// std::cout << " TEST TEST: " << defaultShaderIf->getId() << std::endl;
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
}


void Mesh::DefaultMesh::shaderIdsInit()
{
/*
	std::cout << "shaderIdsInit function called!" << std::endl;

	shaderProgramID = createShader(VertexShader, FragmentShader);
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
*/
}


void Mesh::DefaultMesh::cmdPrompt(const std::string& arg0)
{
	std::cout << "cmdPrompt object: " << m_name << " called with arg: " << arg0 << std::endl;
}
