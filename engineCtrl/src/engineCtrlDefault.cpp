#include "engineCtrlDefault.h"


EngineCtrl::EngineCtrlDefault::EngineCtrlDefault(const std::string& name) : m_name(name)
{
	std::cout << "EngineCtrlDefault created!" << std::endl;
}

EngineCtrl::EngineCtrlDefault::~EngineCtrlDefault()
{
	std::cout << "EngineCtrlDefault destructor called!" << std::endl;
}