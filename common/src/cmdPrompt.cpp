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
			//Common::Factory::getInstance().showMeObjects("ModelIf");
			Common::Factory::getInstance().getModelIf("vanquishModel")->cmdPrompt("dummy");
			Common::Factory::getInstance().getModelIf("cubeModel_0")->cmdPrompt("cubeModel_0");
		}
		std::regex shaders("shaders");
		if (std::regex_search(commandLineString, match, shaders))
		{
			// Common::Factory::getInstance().showMeObjects("ShaderIf");
			FACTORY.getInstance().getShaderIf("normalMapShader_0")->printINFO();
		}

	} while (commandLineString != "run");
}