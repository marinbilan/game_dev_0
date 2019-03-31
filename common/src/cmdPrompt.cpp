#include "cmdPrompt.h"
#include "factory.h"


Common::CmdPrompt::CmdPrompt(Common::Error& err, const std::string& name) : m_name(name)
{
	std::cout << "CmdPrompt created!" << std::endl;
}


Common::CmdPrompt::~CmdPrompt()
{
	std::cout << "CmdPrompt destructor called!" << std::endl;
}


void Common::CmdPrompt::preInit()
{

}


void Common::CmdPrompt::postInit()
{
	std::cout << "CmdPrompt postInit function called!" << std::endl;
	runCmdPrompt();
}


void Common::CmdPrompt::runCmdPrompt()
{
	std::cout << " ---- CmdPrompt runCmdPrompt function called!" << std::endl;

	std::string commandLineString;
	std::smatch match;

	Common::Error err;

	do
	{
		std::cout << "> ";
		std::getline(std::cin, commandLineString);

		/*
		if (!commandLineString.compare("showmeobjects"))
		{
			Common::Factory::getInstance().showMeCommonIfObjects();
		}
		else if (!commandLineString.compare("DefaultModel"))
		{
			Common::Factory::getInstance().showMeModelIfObjects();
		}
		else if (!commandLineString.compare("smartModel_0"))
		{
			Common::Factory::getInstance().getCommonIf(err, commandLineString)->cmdPrompt(commandLineString);
		}
		*/

		// cmd signature
		// 
		Common::Factory::getInstance().getModelIf(commandLineString)->cmdPrompt(commandLineString);
		
	} while (commandLineString != "exit");
}