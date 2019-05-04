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
	// ...
	//
	registerClass();

	createShaders();

	createMeshes();

	createLoaders();

	createModels();

	createCameras();
}


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

	std::cout << " **** RENDER MODEL **** " << '\n';
	Common::Factory::getInstance().getModelIf("smartModel_0")->render();
}


void Init::InitDefault::registerClass()
{
	std::cout << "registerClass function called!" << std::endl;

	// 1] Register Constructor (Class)
	REGISTER_CLASS(Camera::CameraDefault);

	REGISTER_CLASS(Loader::ModelLoader);
	REGISTER_CLASS(Loader::TextureLoader);

	REGISTER_CLASS(GPUObject::TextureGPUObject);
	REGISTER_CLASS(GPUObject::ModelGPUObject);

	REGISTER_CLASS(Model::StaticModel);
	REGISTER_CLASS(Mesh::DefaultMesh);
	REGISTER_CLASS(Shader::DefaultShader);

	Common::Factory::getInstance().showMeSeededClasses();
}


void Init::InitDefault::createCameras()
{
	Common::Error err;

	std::shared_ptr<Camera::CameraDefault> smartCamera_0((Camera::CameraDefault*)Common::Factory::getInstance().constructObject("Camera::CameraDefault", err, "smartCamera_0"));
	Common::Factory::getInstance().storeInContainer("CameraIf", smartCamera_0);

	Common::Factory::getInstance().showMeObjects("CameraIf");
}


void Init::InitDefault::createLoaders()
{
	Common::Error err;

	std::shared_ptr<Loader::ModelLoader> modelLoader_0( (Loader::ModelLoader*)Common::Factory::getInstance().constructObject("Loader::ModelLoader", err, "modelLoader_0") );
	Common::Factory::getInstance().storeInContainer("LoaderIf", modelLoader_0);

	std::shared_ptr<Loader::TextureLoader> textureLoader_0((Loader::TextureLoader*)Common::Factory::getInstance().constructObject("Loader::TextureLoader", err, "textureLoader_0"));
	Common::Factory::getInstance().storeInContainer("LoaderIf", textureLoader_0);

	GLuint texture0 = textureLoader_0->createTexture("_vanquish/textures/texture0.png");
	GLuint texture1 = textureLoader_0->createTexture("_vanquish/textures/texture1.png");
	GLuint texture2 = textureLoader_0->createTexture("_vanquish/textures/texture2.png");
	GLuint texture3 = textureLoader_0->createTexture("_vanquish/textures/texture3.png");
	GLuint texture4 = textureLoader_0->createTexture("_vanquish/textures/texture4.png");
	GLuint texture5 = textureLoader_0->createTexture("_vanquish/textures/texture5.png");

	std::cout << " texture0: " << texture0 << '\n';
	std::cout << " texture1: " << texture1 << '\n';
	std::cout << " texture2: " << texture2 << '\n';
	std::cout << " texture3: " << texture3 << '\n';
	std::cout << " texture4: " << texture4 << '\n';
	std::cout << " texture5: " << texture5 << '\n';

	Common::Factory::getInstance().getMeshIf("smartMesh_0")->setTextureId(texture0);
	Common::Factory::getInstance().getMeshIf("smartMesh_1")->setTextureId(texture1);
	Common::Factory::getInstance().getMeshIf("smartMesh_2")->setTextureId(texture2);
	Common::Factory::getInstance().getMeshIf("smartMesh_3")->setTextureId(texture3);
	Common::Factory::getInstance().getMeshIf("smartMesh_4")->setTextureId(texture4);
	Common::Factory::getInstance().getMeshIf("smartMesh_5")->setTextureId(texture5);

	Common::Factory::getInstance().showMeObjects("LoaderIf");
}


void Init::InitDefault::createModels()
{
	Common::Error err;
	// Create   
	// DB Entry:
	// Create    ModelIf    Model::StaticModel    smartModel_0
	// Model object                                                                                                   Model::StaticModel       .. /modelPath/    smartModel_0
	std::shared_ptr<Model::ModelIf> smartModel_0((Model::StaticModel*)Common::Factory::getInstance().constructObject("Model::StaticModel", err, "smartModel_0") );
	Common::Factory::getInstance().storeInContainer("ModelIf", smartModel_0);

	Common::Factory::getInstance().showMeObjects("ModelIf");
}


void Init::InitDefault::createMeshes()
{
	Common::Error err;

	std::shared_ptr<Mesh::DefaultMesh> smartMesh_0((Mesh::DefaultMesh*)Common::Factory::getInstance().constructObject("Mesh::DefaultMesh", err, "smartMesh_0"));
	Common::Factory::getInstance().storeInContainer("MeshIf", smartMesh_0);

	std::shared_ptr<Mesh::DefaultMesh> smartMesh_1((Mesh::DefaultMesh*)Common::Factory::getInstance().constructObject("Mesh::DefaultMesh", err, "smartMesh_1"));
	Common::Factory::getInstance().storeInContainer("MeshIf", smartMesh_1);

	std::shared_ptr<Mesh::DefaultMesh> smartMesh_2((Mesh::DefaultMesh*)Common::Factory::getInstance().constructObject("Mesh::DefaultMesh", err, "smartMesh_2"));
	Common::Factory::getInstance().storeInContainer("MeshIf", smartMesh_2);

	std::shared_ptr<Mesh::DefaultMesh> smartMesh_3((Mesh::DefaultMesh*)Common::Factory::getInstance().constructObject("Mesh::DefaultMesh", err, "smartMesh_3"));
	Common::Factory::getInstance().storeInContainer("MeshIf", smartMesh_3);

	std::shared_ptr<Mesh::DefaultMesh> smartMesh_4((Mesh::DefaultMesh*)Common::Factory::getInstance().constructObject("Mesh::DefaultMesh", err, "smartMesh_4"));
	Common::Factory::getInstance().storeInContainer("MeshIf", smartMesh_4);

	std::shared_ptr<Mesh::DefaultMesh> smartMesh_5((Mesh::DefaultMesh*)Common::Factory::getInstance().constructObject("Mesh::DefaultMesh", err, "smartMesh_5"));
	Common::Factory::getInstance().storeInContainer("MeshIf", smartMesh_5);

	Common::Factory::getInstance().showMeObjects("MeshIf");
}


void Init::InitDefault::createShaders()
{
	Common::Error err;

	std::shared_ptr<Shader::DefaultShader> smartShader_0((Shader::DefaultShader*)Common::Factory::getInstance().constructObject("Shader::DefaultShader", err, "smartShader_0"));
    // smartShader_0->printINFO();
	Common::Factory::getInstance().storeInContainer("ShaderIf", smartShader_0);

	Common::Factory::getInstance().showMeObjects("ShaderIf");
}


