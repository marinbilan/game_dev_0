#include "initDefault.h"
#include "error.h"
#include "factory.h"


class Widget
{
public:
	Widget(Common::Error& err, const std::string& name) : m_name(name) {}

private:
	std::string m_name;
};


Init::InitDefault::InitDefault(Common::Error& err, const std::string& name) : m_name(name)
{
	std::cout << "InitDefault created!" << std::endl;
}

Init::InitDefault::~InitDefault()
{
	std::cout << "InitDefault destructor called!" << std::endl;
}


void Init::InitDefault::preInit()
{
	std::cout << "preInit function called!" << std::endl;
	// Get stuff from db
	
	registerClass();

	createDefaultObject();
}


void Init::InitDefault::postInit()
{
	std::cout << "postInit function called!" << std::endl;
}


void Init::InitDefault::registerClass()
{
	std::cout << "registerClass function called!" << std::endl;

	// 1] Register Constructor (Class)
	REGISTER_CLASS(Widget);

	defaultFactory.showMeSeededClasses();

}


void Init::InitDefault::createDefaultObject()
{
	std::cout << "createDefaultObject function called!" << std::endl;

	// 2] FIND in MAP (first) seeded objects - and - INSTANTIATE OBJECT (second) 
	// Function  
	// Create                                                                     Widget         .. /modelPath/    widget_0
	Common::Error err;
	std::shared_ptr<Widget> smartWidget0((Widget*)defaultFactory.constructObject("Widget", err, "Widget_0"));
}
