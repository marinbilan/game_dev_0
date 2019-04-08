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
	std::string commandLineString;
	std::smatch match;

	Common::Error err;
	
	std::cout << " ---- Available objects: " << std::endl;

	Common::Factory::getInstance().showMeObjects("LoaderIf");
	Common::Factory::getInstance().showMeObjects("GPUObjectIf");
	Common::Factory::getInstance().showMeObjects("ModelIf");
	Common::Factory::getInstance().showMeObjects("MeshIf");
	Common::Factory::getInstance().showMeObjects("ShaderIf");
	
	std::cout << " ---- ---- " << std::endl;

	do
	{
		std::cout << "$ ";
		std::getline(std::cin, commandLineString);

		Common::Factory::getInstance().getModelIf(commandLineString)->cmdPrompt(commandLineString);
		Common::Factory::getInstance().getMeshIf(commandLineString)->cmdPrompt(commandLineString);
		Common::Factory::getInstance().getShaderIf(commandLineString)->cmdPrompt(commandLineString);

	} while (commandLineString != "exit");
}