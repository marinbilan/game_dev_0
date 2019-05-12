#include "engineCtrlDefault.h"


EngineCtrl::EngineCtrlDefault::EngineCtrlDefault(Common::Error& err, const std::string& name) : m_name(name)
{
	std::cout << "EngineCtrl::EngineCtrlDefault::EngineCtrlDefault() constructor called" << '\n';
}


EngineCtrl::EngineCtrlDefault::~EngineCtrlDefault()
{
	std::cout << "EngineCtrl::EngineCtrlDefault::~EngineCtrlDefault() destructor called" << '\n';
}


void EngineCtrl::EngineCtrlDefault::databaseInit(const std::string& dbName)
{
	Common::Error err;

	// Create DB and store it in Factory
	std::unique_ptr<Common::Database> database = std::make_unique<Common::Database>(err, "sw/_db/database_0.txt");
	Common::Factory::getInstance().setDatabase(database);
		
}


void EngineCtrl::EngineCtrlDefault::preInit()
{
	std::cout << "EngineCtrl::EngineCtrlDefault::preInit() called" << '\n';

	// Get stuff from db
	Common::Error err;

	// Create defaultInit 
	defaultInit0 = new Init::InitDefault(err, "DefaultInit0");


	// Init All Objects
	defaultInit0->preInit();

	// Create cmdPrompt
	cmdPrompt0 = new Common::CmdPrompt(err, "CmdPrompt0");
}


void EngineCtrl::EngineCtrlDefault::postInit()
{
	std::cout << "EngineCtrl::EngineCtrlDefault::postInit() called" << '\n';

	defaultInit0->postInit();

	cmdPrompt0->runCmdPrompt();
	
}

