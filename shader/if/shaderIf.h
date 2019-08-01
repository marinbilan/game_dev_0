#pragma once
#include <iostream>

#include "glew.h"
#include "glfw3.h"

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

	virtual void preInit() {};
	virtual void postInit() {};

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

	// OPERATORs
	virtual void printINFO() {};

	virtual void cmdPrompt(const std::string& arg0)
	{
		
	}

private:
std::string dummyString;
};
}