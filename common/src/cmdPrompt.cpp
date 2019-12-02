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

		std::regex oneWordLine("(\\w+)");

		// One word match
		if (std::regex_search(commandLineString, match, oneWordLine))
		{
			if (!match.str(1).compare("models"))
			{
				cmdModels(commandLineString);
			}
			if (!match.str(1).compare("help"))
			{
				cmdHelp();
			}
		}
	} while (commandLineString != "run");
}


void Common::CmdPrompt::cmdModels(const std::string& str)
{
	std::smatch match;

	if (!str.compare("models"))
	{
		std::cout << " models <modelName | all>" << std::endl;
	}

	std::regex twoWordLine("models\\s+(\\w+)");
	if (std::regex_search(str, match, twoWordLine))
	{
		if (!match.str(1).compare("all"))
		{
			for (auto s : FACTORY.getModelIfVec())
			{
			    std::cout << " - " << (*s).getName() << '\n';
			}
		}
		else
		{
			std::cout << " Print something second word: " << match.str(1) << '\n';
		}
	}

}


void Common::CmdPrompt::cmdHelp()
{
	std::cout << "" << std::endl;
	std::cout << " ----==== HELP ====---- " << std::endl;
	std::cout << "" << std::endl;
	std::cout << " cameras   Info about cameras In scene " << std::endl;
	std::cout << " controls  Info about controls (Keys)" << std::endl;
	std::cout << " models    Info about Models, Meshes and Textures in scene" << std::endl;
	std::cout << " shaders   Info about Shaders and Shader Parameters" << std::endl;
	std::cout << " read      Read from File" << std::endl;
	std::cout << "" << std::endl;
	std::cout << " ---------------------" << std::endl;
}
