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

	// cmd handling
	void cmdModels(const std::string& str);
	void cmdHelp();

private:
std::string m_name;
};
}