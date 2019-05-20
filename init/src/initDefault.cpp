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

}


// Combine all things together
void Init::InitDefault::postInit()
{
	std::cout << "[initDefault] postInit function called!" << std::endl;

	// Add shaders private members
	// ...

	// Connect shader and mesh
	Common::Factory::getInstance().getMeshIf("smartMesh_0")->setShader(Common::Factory::getInstance().getShaderIf("smartShader_0"));
	Common::Factory::getInstance().getMeshIf("smartMesh_1")->setShader(Common::Factory::getInstance().getShaderIf("smartShader_0"));
	Common::Factory::getInstance().getMeshIf("smartMesh_2")->setShader(Common::Factory::getInstance().getShaderIf("smartShader_0"));
	Common::Factory::getInstance().getMeshIf("smartMesh_3")->setShader(Common::Factory::getInstance().getShaderIf("smartShader_0"));
	Common::Factory::getInstance().getMeshIf("smartMesh_4")->setShader(Common::Factory::getInstance().getShaderIf("smartShader_0"));
	Common::Factory::getInstance().getMeshIf("smartMesh_5")->setShader(Common::Factory::getInstance().getShaderIf("smartShader_0"));

	// Connect mesh and model
	Common::Factory::getInstance().getModelIf("smartModel_0")->setMesh(Common::Factory::getInstance().getMeshIf("smartMesh_0"));
	Common::Factory::getInstance().getModelIf("smartModel_0")->setMesh(Common::Factory::getInstance().getMeshIf("smartMesh_1"));
	Common::Factory::getInstance().getModelIf("smartModel_0")->setMesh(Common::Factory::getInstance().getMeshIf("smartMesh_2"));
	Common::Factory::getInstance().getModelIf("smartModel_0")->setMesh(Common::Factory::getInstance().getMeshIf("smartMesh_3"));
	Common::Factory::getInstance().getModelIf("smartModel_0")->setMesh(Common::Factory::getInstance().getMeshIf("smartMesh_4"));
	Common::Factory::getInstance().getModelIf("smartModel_0")->setMesh(Common::Factory::getInstance().getMeshIf("smartMesh_5"));

	// Connect GPUObject and SmartModel
	Common::Factory::getInstance().getModelIf("smartModel_0")->setGPUObject(Common::Factory::getInstance().getGPUObjectIf("vanquishGPUObject"));
	Common::Factory::getInstance().getModelIf("smartModel_0")->connect();

	// Connect Camera and SmartModel
	Common::Factory::getInstance().getMeshIf("smartMesh_0")->setCamera(Common::Factory::getInstance().getCameraIf("smartCamera_0"));
	Common::Factory::getInstance().getMeshIf("smartMesh_1")->setCamera(Common::Factory::getInstance().getCameraIf("smartCamera_0"));
	Common::Factory::getInstance().getMeshIf("smartMesh_2")->setCamera(Common::Factory::getInstance().getCameraIf("smartCamera_0"));
	Common::Factory::getInstance().getMeshIf("smartMesh_3")->setCamera(Common::Factory::getInstance().getCameraIf("smartCamera_0"));
	Common::Factory::getInstance().getMeshIf("smartMesh_4")->setCamera(Common::Factory::getInstance().getCameraIf("smartCamera_0"));
	Common::Factory::getInstance().getMeshIf("smartMesh_5")->setCamera(Common::Factory::getInstance().getCameraIf("smartCamera_0"));

	// Combiner
//
// TODO: Combine inside instances
	GLuint texture0 = Common::Factory::getInstance().getLoaderIf("textureLoader_0")->createTexture("_vanquish/textures/texture0.png");
	GLuint texture1 = Common::Factory::getInstance().getLoaderIf("textureLoader_0")->createTexture("_vanquish/textures/texture1.png");
	GLuint texture2 = Common::Factory::getInstance().getLoaderIf("textureLoader_0")->createTexture("_vanquish/textures/texture2.png");
	GLuint texture3 = Common::Factory::getInstance().getLoaderIf("textureLoader_0")->createTexture("_vanquish/textures/texture3.png");
	GLuint texture4 = Common::Factory::getInstance().getLoaderIf("textureLoader_0")->createTexture("_vanquish/textures/texture4.png");
	GLuint texture5 = Common::Factory::getInstance().getLoaderIf("textureLoader_0")->createTexture("_vanquish/textures/texture5.png");


	Common::Factory::getInstance().getMeshIf("smartMesh_0")->setTextureId(texture0);
	Common::Factory::getInstance().getMeshIf("smartMesh_1")->setTextureId(texture1);
	Common::Factory::getInstance().getMeshIf("smartMesh_2")->setTextureId(texture2);
	Common::Factory::getInstance().getMeshIf("smartMesh_3")->setTextureId(texture3);
	Common::Factory::getInstance().getMeshIf("smartMesh_4")->setTextureId(texture4);
	Common::Factory::getInstance().getMeshIf("smartMesh_5")->setTextureId(texture5);

	//std::cout << " **** RENDER MODEL **** " << '\n';
	//Common::Factory::getInstance().getModelIf("smartModel_0")->render();
}
