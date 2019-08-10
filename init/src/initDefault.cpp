#include "initDefault.h"

#include "factory.h"


Init::InitDefault::InitDefault(const std::string& name) : m_name(name)
{
}


Init::InitDefault::~InitDefault()
{
}


void Init::InitDefault::preInit()
{
	// FACTORY
	FACTORY.preInit();

	FACTORY.getModelIf("smartModel_0")->preInit();
}


// Combine all things together
void Init::InitDefault::postInit()
{
	// TODO: Move in preInit
	Common::Factory::getInstance().getLoaderIf("textureLoader_0")->preInit();

	FACTORY.getModelIf("smartModel_0")->postInit();

}
