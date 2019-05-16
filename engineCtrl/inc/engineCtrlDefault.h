#pragma once
#include "engineCtrlIf.h"

#include <iostream>
#include <string>

#include "error.h"

#include "initIf.h"
#include "initDefault.h"
#include "cmdPrompt.h"
#include "database.h"
#include "factory.h"


namespace EngineCtrl
{
class EngineCtrlDefault : public EngineCtrlIf
{
public:
	EngineCtrlDefault(Common::Error& err, const std::string& name);

	~EngineCtrlDefault();

	// Error init before preInit and postInit
	void errorInit();
	// Database init before preInit and postInit
	void databaseInit(const std::string& dbName);

	void preInit();
	void postInit();

private:
std::string m_name;

// TODO: uniquePtr
Init::InitIf* defaultInit0;
Common::CmdPrompt* cmdPrompt0;
};
}