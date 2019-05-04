#include "lightDefault.h"


Light::LightDefault::LightDefault(Common::Error& err, const std::string& name) : m_name(name)
{
	std::cout << "Light::LightDefault::LightDefault() constructor called!" << '\n';
}


Light::LightDefault::~LightDefault()
{
	std::cout << "Light::LightDefault::~LightDefault() destructor called!" << '\n';
}


void Light::LightDefault::preInit()
{
	std::cout << "Light::LightDefault::preInit() called!" << '\n';
}


void Light::LightDefault::postInit()
{
	std::cout << "Light::LightDefault::postInit() called!" << '\n';
}

