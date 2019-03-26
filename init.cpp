#include <iostream>

// Common
#include "commonIf.h"
#include "error.h"
#include "factory.h"

// EngineCtrl
#include "engineCtrlIf.h"
#include "engineCtrlDefault.h"

class Widget
{
public:
	Widget(Common::Error& err, const std::string& name) : m_name(name) {}

private:
	std::string m_name;
};

int main ()
{
	Common::Error err;
	err.setError("This is error");
	err.printError();

	{
		EngineCtrl::EngineCtrlDefault engineCtrl0("engineControl");
	}

	REGISTER_CLASS(Widget);

	defaultFactory.showMeSeededClasses();

	// 2] FIND in MAP (first) seeded objects - and - INSTANTIATE OBJECT (second) 
	// Function                // REGISTERED  Class name    // raw model name (raw_model_0.3ds)  
	// CreateWidget                                                               Widget         .. /modelPath/    widget_0
	std::shared_ptr<Widget> smartWidget0((Widget*)defaultFactory.constructObject("Widget", err, "Widget_0"));

	char c;
	std::cin >> c;
	return 0;
};