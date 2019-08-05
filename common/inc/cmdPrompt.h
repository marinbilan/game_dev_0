#pragma once

#include <string>
#include <iostream>
#include <regex>

namespace Common
{
class CmdPrompt
{
public:
	CmdPrompt(const std::string& name);
	~CmdPrompt();

	void preInit();
	void postInit();

	void runCmdPrompt();

private:
std::string m_name;
};
}