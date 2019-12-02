#pragma once 

#include "engineCtrlIf.h"
#include "engineCtrlDefault.h"



int main (int argc, char** argv)
{
	// std::cout << "You have entered " << argc << " arguments:" << "\n";	
	// for (int i = 0; i < argc; ++i) std::cout << argv[i] << "\n";

	EngineCtrl::EngineCtrlDefault engineCtrl0("engineControl");
	engineCtrl0.databaseInit("sw/_db/database_0.txt");
	
	// Init
	engineCtrl0.glfwInitialization();

	engineCtrl0.preInitialization();
	engineCtrl0.postInitialization();

	// current date/time based on current system
	// #include <ctime>
	// time_t now = time(0);
	// convert now to string form
	/*char* dt = ctime(&now);
	std::string log0(dt);
	std::cout << "The local date and time is: " << log0 << std::endl;*/

	return 0;
};