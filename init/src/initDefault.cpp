#include "initDefault.h"

#include "factory.h"

#include "cameraIf.h"
#include "cameraDefault.h"

#include "loaderIf.h"
#include "modelLoader.h"
#include "textureLoader.h"

#include "gpuObjectIf.h"
#include "modelGPUObject.h"
#include "textureGPUObject.h"

#include "modelIf.h"
#include "staticModel.h"

#include "meshIf.h"
#include "defaultMesh.h"

#include "shaderIf.h"
#include "defaultShader.h"

#include "commonTypes.h"


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
	std::cout << "[initDefault] postInit function called!" << std::endl;


	// TODO: Move in preInit
	Common::Factory::getInstance().getLoaderIf("textureLoader_0")->preInit();


	// Connect Camera and SmartModel
	FACTORY.getMeshIf("smartMesh_0")->postInit();
	FACTORY.getMeshIf("smartMesh_1")->postInit();
	FACTORY.getMeshIf("smartMesh_2")->postInit();
	FACTORY.getMeshIf("smartMesh_3")->postInit();
	FACTORY.getMeshIf("smartMesh_4")->postInit();
	FACTORY.getMeshIf("smartMesh_5")->postInit();


	FACTORY.getModelIf("smartModel_0")->postInit();








	/*


	GLuint texture0 = Common::Factory::getInstance().getLoaderIf("textureLoader_0")->createTexture("_vanquish/textures/texture0.png");
	std::cout << " ************ " << FACTORY.getGPUObjectIf("_vanquish/textures/texture0.png")->getTextureID() << '\n';

	// FACTORY.getGPUObjectIf("_vanquish/textures/texture0.png")->getTextureID();

	GLuint texture1 = Common::Factory::getInstance().getLoaderIf("textureLoader_0")->createTexture("_vanquish/textures/texture1.png");
	std::cout << " ************ " << FACTORY.getGPUObjectIf("_vanquish/textures/texture1.png")->getTextureID() << '\n';



	GLuint texture2 = Common::Factory::getInstance().getLoaderIf("textureLoader_0")->createTexture("_vanquish/textures/texture2.png");
	GLuint texture3 = Common::Factory::getInstance().getLoaderIf("textureLoader_0")->createTexture("_vanquish/textures/texture3.png");
	GLuint texture4 = Common::Factory::getInstance().getLoaderIf("textureLoader_0")->createTexture("_vanquish/textures/texture4.png");
	GLuint texture5 = Common::Factory::getInstance().getLoaderIf("textureLoader_0")->createTexture("_vanquish/textures/texture5.png");
	*/




	// TODO: remove
	/*
	Common::Factory::getInstance().getMeshIf("smartMesh_0")->setTextureId(texture0);
	Common::Factory::getInstance().getMeshIf("smartMesh_1")->setTextureId(texture1);
	Common::Factory::getInstance().getMeshIf("smartMesh_2")->setTextureId(texture2);
	Common::Factory::getInstance().getMeshIf("smartMesh_3")->setTextureId(texture3);
	Common::Factory::getInstance().getMeshIf("smartMesh_4")->setTextureId(texture4);
	Common::Factory::getInstance().getMeshIf("smartMesh_5")->setTextureId(texture5);
	*/

	/*
	Common::Factory::getInstance().getMeshIf("smartMesh_0")->setTextureId( FACTORY.getGPUObjectIf("_vanquish/textures/texture0.png")->getTextureID() );
	Common::Factory::getInstance().getMeshIf("smartMesh_1")->setTextureId(FACTORY.getGPUObjectIf("_vanquish/textures/texture1.png")->getTextureID());
	Common::Factory::getInstance().getMeshIf("smartMesh_2")->setTextureId(FACTORY.getGPUObjectIf("_vanquish/textures/texture2.png")->getTextureID());
	Common::Factory::getInstance().getMeshIf("smartMesh_3")->setTextureId(FACTORY.getGPUObjectIf("_vanquish/textures/texture3.png")->getTextureID());
	Common::Factory::getInstance().getMeshIf("smartMesh_4")->setTextureId(FACTORY.getGPUObjectIf("_vanquish/textures/texture4.png")->getTextureID());
	Common::Factory::getInstance().getMeshIf("smartMesh_5")->setTextureId(FACTORY.getGPUObjectIf("_vanquish/textures/texture5.png")->getTextureID());
	*/
}
