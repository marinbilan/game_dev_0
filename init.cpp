#include <iostream>

#include "error.h"

// EngineCtrl
#include "engineCtrlIf.h"
#include "engineCtrlDefault.h"



int main ()
{
	Common::Error err;

	EngineCtrl::EngineCtrlDefault engineCtrl0(err, "engineControl");
	engineCtrl0.preInit();
	engineCtrl0.postInit();


	return 0;
};