#include "templateDefault.h"
#include "error.h"


Template::TemplateDefault::TemplateDefault(Common::Error& err, const std::string& name) : m_name(name)
{
	std::cout << "TemplateDefault created!" << std::endl;
}


Template::TemplateDefault::~TemplateDefault()
{
	std::cout << "TemplateDefault destructor called!" << std::endl;
}


void Template::TemplateDefault::preInit()
{

}


void Template::TemplateDefault::postInit()
{
	std::cout << "postInit function called!" << std::endl;
}

