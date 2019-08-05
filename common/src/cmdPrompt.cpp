#include "cmdPrompt.h"
#include "factory.h"


Common::CmdPrompt::CmdPrompt(const std::string& name) : m_name(name)
{
	std::cout << "CmdPrompt " << m_name << " created!" << std::endl;
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

	// Common::Factory::getInstance().showMeObjects("LoaderIf");

	do
	{
		std::cout << "$ ";
		// Waiting for command
		std::getline(std::cin, commandLineString);

		Common::Factory::getInstance().getModelIf(commandLineString)->cmdPrompt(commandLineString);
		// Common::Factory::getInstance().getMeshIf(commandLineString)->cmdPrompt(commandLineString);
		// Common::Factory::getInstance().getShaderIf(commandLineString)->cmdPrompt(commandLineString);

	} while (commandLineString != "exit");
}