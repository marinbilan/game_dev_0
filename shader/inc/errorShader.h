#pragma once
#include "shaderIf.h"

#include "error.h"


namespace Shader
{
class ErrorShader : public ShaderIf
{
public:
	ErrorShader(Common::Error& err, const std::string& name) {};

	~ErrorShader() {};

	int getId() { return 0; }

	// ShaderIf
	void preInit() {};
	void postInit() {};

	const std::string& getName() 
	{ 
		return m_name; 
	}

	void cmdPrompt(const std::string& arg0) 
	{
		std::cout << "ERROR: ErrorShader called!" << std::endl;
	};

private:
std::string m_name;
};
}