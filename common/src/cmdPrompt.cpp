#include "cmdPrompt.h"
#include "factory.h"


Common::CmdPrompt::CmdPrompt(const std::string& name) : m_name(name)
{
}


Common::CmdPrompt::~CmdPrompt()
{
}


void Common::CmdPrompt::preInit()
{
}


void Common::CmdPrompt::postInit()
{
	runCmdPrompt();
}


void Common::CmdPrompt::runCmdPrompt()
{
	std::string commandLineString;
	std::smatch match;

	do
	{
		std::cout << "$ ";
		// Waiting for command
		std::getline(std::cin, commandLineString);

		std::regex models("models");
		if (std::regex_search(commandLineString, match, models))
		{
			Common::Factory::getInstance().showMeObjects("ModelIf");
		}
		std::regex shaders("shaders");
		if (std::regex_search(commandLineString, match, shaders))
		{
			// Common::Factory::getInstance().showMeObjects("ShaderIf");
			FACTORY.getInstance().getShaderIf("terrain0")->printINFO();
		}

	} while (commandLineString != "run");
}