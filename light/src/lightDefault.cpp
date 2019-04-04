#include "lightDefault.h"
#include "error.h"


Light::LightDefault::LightDefault(Common::Error& err, const std::string& name) : m_name(name)
{
	std::cout << "LightDefault created!" << std::endl;
}


Light::LightDefault::~LightDefault()
{
	std::cout << "LightDefault destructor called!" << std::endl;
}


void Light::LightDefault::preInit()
{

}


void Light::LightDefault::postInit()
{
	std::cout << "postInit function called!" << std::endl;
}

