#pragma once
#include <iostream>


namespace EngineCtrl
{
class EngineCtrlIf
{
public:
	~EngineCtrlIf()
	{
		std::cout << "EngineCtrlDefaultIf destructor called!" << std::endl;
	}

};
}