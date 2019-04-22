#pragma once
#include <iostream>

#include "glew.h"
#include "glfw3.h"

// TODO: Include glm projection matrix
#include "glm.hpp"
#include "gtc/matrix_transform.hpp" // For projection matrix


namespace Shader
{
class ShaderIf
{
public:
	~ShaderIf()
	{
		std::cout << "ShaderIf destructor called!" << std::endl;
	}

	virtual const std::string& getName()
	{
		return "not implemented in MeshIf";
	}

	// FUNCTIONs
	virtual GLuint createShader(const char* vertexShader, const char* fragmentShader)
	{
		// Make VertexShader
		GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderID, 1, (const GLchar**)&vertexShader, NULL);
		glCompileShader(vertexShaderID);
		// Make FragmentShader
		GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderID, 1, (const GLchar**)&fragmentShader, NULL);
		glCompileShader(fragmentShaderID);
		// Make Shader Program
		GLuint shaderID = glCreateProgram();
		glAttachShader(shaderID, vertexShaderID);
		glAttachShader(shaderID, fragmentShaderID);
		glLinkProgram(shaderID);

		return shaderID;
	}

	virtual std::string  getShaderName() { return dummyString; }
	virtual GLuint const getShaderProgramID()      const { return 0; }

	// [ VERTEX SHADER ]
	//   ATTRIBs
	// ------------------- [ ShaderPTN0 ] --------------------------
	virtual GLuint const getPositionsID()        const { return 0; }
	virtual GLuint const getTextureCoordsID()    const { return 0; }
	virtual GLuint const getNormalsID()          const { return 0; }
	//   UNIFORMs
	virtual GLuint const getProjectionMatrixID() const { return 0; }
	virtual GLuint const getViewMatrixID()       const { return 0; }
	virtual GLuint const getViewMatrixInvID()    const { return 0; }
	virtual GLuint const getModelMatrixID()      const { return 0; }

	virtual GLuint const getLightPositionID()    const { return 0; }
	virtual GLuint const getPlaneID()            const { return 0; }
	// [ FRAGMENT SHADER ]
	//   UNIFORMs
	virtual GLuint const getLightColorID()       const { return 0; }
	virtual GLuint const getShineDamperID()      const { return 0; }
	virtual GLuint const getReflectivityID()     const { return 0; }
	virtual GLuint const getModelTextureID()     const { return 0; }
	// -------------------------------------------------------------


	virtual int getId() { return 0; }

	virtual void preInit() {};
	virtual void postInit() {};

	// OPERATORs
	virtual void printINFO() {};

	virtual void cmdPrompt(const std::string& arg0)
	{
		std::cout << "Error: Not implemented function - calling from ComminIf" << std::endl;
	}

private:
std::string dummyString;
};
}