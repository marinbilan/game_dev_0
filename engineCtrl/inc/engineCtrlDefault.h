#pragma once
#include <iostream>
#include <string>

#include "error.h"

#include "engineCtrlIf.h"

#include "initIf.h"
#include "initDefault.h"
#include "cmdPrompt.h"


namespace EngineCtrl
{
class EngineCtrlDefault : public EngineCtrlIf
{
public:
	EngineCtrlDefault(Common::Error& err, const std::string& name);

	~EngineCtrlDefault();

	void preInit();

	void postInit();

private:
	std::string m_name;

	// TODO: uniquePtr
	Init::InitIf* defaultInit0;
	Common::CmdPrompt* cmdPrompt0;
};
}