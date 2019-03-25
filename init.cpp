#include <iostream>

#include "engineCtrlIf.h"
#include "engineCtrlDefault.h"

int main ()
{
	{
		EngineCtrl::EngineCtrlDefault engineCtrl0("engineControl");
	}

	char c;
	std::cin >> c;
	return 0;
};