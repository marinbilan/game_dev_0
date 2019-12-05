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
	// ----
	std::istringstream stringOfElements(str);
	std::vector<std::string> vectorOfLocalStrings((std::istream_iterator<std::string>(stringOfElements)), std::istream_iterator<std::string>());

	std::string regexPattern;
	if (vectorOfLocalStrings.size() == 1)
	{
		regexPattern = "models";
	}
	if (vectorOfLocalStrings.size() == 2)
	{
		regexPattern = "models\\s+(\\w+)";
	}
	else if (vectorOfLocalStrings.size() == 3)
	{
		regexPattern = "models\\s+(\\w+)\\s+(\\w+)";
	}
	// ----

	std::smatch match;
	std::regex _regex(regexPattern);
	if (std::regex_search(str, match, _regex))
	{
		// One word in cmd line
		if (vectorOfLocalStrings.size() == 1)
		{
			std::cout << " models <modelName | all>" << std::endl;
		}
		// Two words in cmd line or Three words in cmd line
		else if (vectorOfLocalStrings.size() == 2 | 
			     vectorOfLocalStrings.size() == 3)
		{
			if (!match.str(1).compare("all"))
			{
				for (auto s : FACTORY.getModelIfVec())
				{
				    std::cout << " - " << s->getName() << '\n';
				}
			}
			else 
			{
				for (auto s : FACTORY.getModelIfVec())
				{
					if (!match.str(1).compare(s->getName()))
					{
						s->cmdPrompt(str);
					}
				}
			}
		}
	}
}


void Common::CmdPrompt::cmdHelp()
{
	std::cout << " [ HELP ] " << std::endl;
	std::cout << " cameras   Info about cameras In scene " << std::endl;
	std::cout << " controls  Info about controls (Keys)" << std::endl;
	std::cout << " models    Info about Models, Meshes and Textures in scene" << std::endl;
	std::cout << " shaders   Info about Shaders and Shader Parameters" << std::endl;
	std::cout << " read      Read from File" << std::endl;
}
