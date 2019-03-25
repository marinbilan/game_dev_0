#pragma once
#include <iostream>
#include <string>

#include "engineCtrlIf.h"


namespace EngineCtrl
{
class EngineCtrlDefault : public EngineCtrlIf
{
public:
	EngineCtrlDefault(const std::string& name);

	~EngineCtrlDefault();

private:
	std::string m_name;
};
}