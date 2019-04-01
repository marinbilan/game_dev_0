#pragma once
#include "shaderIf.h"

#include "error.h"

namespace Shader
{
class DefaultShader : public ShaderIf
{
public:
	DefaultShader(Common::Error& err, const std::string& name);

	~DefaultShader();

	int getId();

	const std::string& getName()
	{
		return m_name;
	}

	void preInit();
	void postInit();

	void cmdPrompt(const std::string& arg0);

private:
std::string m_name;
};
}