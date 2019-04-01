#include "engineCtrlDefault.h"


EngineCtrl::EngineCtrlDefault::EngineCtrlDefault(Common::Error& err, const std::string& name) : m_name(name)
{
	std::cout << "EngineCtrlDefault created!" << std::endl;
}

EngineCtrl::EngineCtrlDefault::~EngineCtrlDefault()
{
	std::cout << "EngineCtrlDefault destructor called!" << std::endl;
}

void EngineCtrl::EngineCtrlDefault::preInit()
{
	std::cout << "preInit function called!" << std::endl;
	// Get stuff from db
	

	// Create defaultInit 
	Common::Error err;
	defaultInit0 = new Init::InitDefault(err, "DefaultInit0");
	defaultInit0->preInit();

	// Create cmdPrompt
	cmdPrompt0 = new Common::CmdPrompt(err, "CmdPrompt0");
}

void EngineCtrl::EngineCtrlDefault::postInit()
{
	std::cout << "postInit function called!" << std::endl;

	defaultInit0->postInit();
	cmdPrompt0->runCmdPrompt();
	
}

