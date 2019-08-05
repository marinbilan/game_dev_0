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

	// TODO: foreach object
	FACTORY.getMeshIf("smartMesh_0")->preInit();
	FACTORY.getMeshIf("smartMesh_1")->preInit();
	FACTORY.getMeshIf("smartMesh_2")->preInit();
	FACTORY.getMeshIf("smartMesh_3")->preInit();
	FACTORY.getMeshIf("smartMesh_4")->preInit();
	FACTORY.getMeshIf("smartMesh_5")->preInit();

	FACTORY.getModelIf("smartModel_0")->preInit();
}


// Combine all things together
void Init::InitDefault::postInit()
{
	// TODO: Move in preInit
	Common::Factory::getInstance().getLoaderIf("textureLoader_0")->preInit();

	FACTORY.getMeshIf("smartMesh_0")->postInit();
	FACTORY.getMeshIf("smartMesh_1")->postInit();
	FACTORY.getMeshIf("smartMesh_2")->postInit();
	FACTORY.getMeshIf("smartMesh_3")->postInit();
	FACTORY.getMeshIf("smartMesh_4")->postInit();
	FACTORY.getMeshIf("smartMesh_5")->postInit();

	FACTORY.getModelIf("smartModel_0")->postInit();

}
