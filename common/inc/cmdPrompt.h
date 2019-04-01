#pragma once
#include "error.h"

#include <string>
#include <iostream>
#include <regex>

namespace Common
{
class CmdPrompt
{
public:
	CmdPrompt(Common::Error& err, const std::string& name);

	~CmdPrompt();

	void preInit();
	void postInit();

	void runCmdPrompt();

private:
std::string m_name;
std::string m_error;
};
}