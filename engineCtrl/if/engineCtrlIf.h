#pragma once
#include <iostream>


namespace EngineCtrl
{
class EngineCtrlIf
{
public:
	~EngineCtrlIf()
	{
		std::cout << "Error: EngineCtrlIf::~EngineCtrlIf() called from EngineCtrlIf!" << '\n';
	}

	virtual void preInit() {};
	virtual void postInit() {};

	// Render
};
}