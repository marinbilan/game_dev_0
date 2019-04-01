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