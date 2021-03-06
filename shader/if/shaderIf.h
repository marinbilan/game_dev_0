#pragma once
#include <iostream>

#include "glew.h"
#include "glfw3.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp" // For projection matrix

#include "commonTypes.h"

#include "cameraIf.h"
#include "lightIf.h"
#include "gpuObjectIf.h"


namespace Shader
{
class ShaderIf
{
public:
	~ShaderIf()
	{
		std::cout << "ShaderIf destructor called!" << std::endl;
	}

	virtual void preInitialization() {};
	virtual void postInitialization() {};

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

	virtual void render(const glm::mat4& modelMatrix,
		const GPUObject::MeshStructure modelMesh,
		const GPUObject::TextureStructure textureStruct,
		const std::shared_ptr<Camera::CameraIf>& camera,
		const std::shared_ptr<Light::LightIf>& light) {};

	// Terrain Renderer
	virtual void render(GLuint VAO, 
		std::shared_ptr<Camera::CameraIf>& m_cameraIf, 
		const std::shared_ptr<Light::LightIf>& light, 
		glm::mat4& m_modelMatrix, 
		const GPUObject::TextureStructure textureStruct, 
		GLuint numInd) {};

	// OPERATORs
	virtual void printINFO() {};

	virtual void cmdPrompt(const std::string& arg0)
	{
		
	}

private:
std::string dummyString;
};
}