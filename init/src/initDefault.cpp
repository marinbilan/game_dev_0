#include "initDefault.h"

#include "factory.h"
#include "error.h"

#include "modelIf.h"
#include "staticModel.h"

#include "meshIf.h"
#include "defaultMesh.h"

#include "shaderIf.h"
#include "defaultShader.h"

#include "loaderIf.h"
#include "modelLoader.h"
#include "textureLoader.h"

#include "gpuObjectIf.h"
#include "modelGPUObject.h"
#include "textureGPUObject.h"


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

	// Test
	std::cout << " NUM OF INSTANCES after LOADER: " << Common::Factory::getInstance().getGPUObjectIf("vanquishGPUObject").use_count() << "\n";
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

	std::cout << " **** RENDER MODEL **** " << '\n';
	Common::Factory::getInstance().getModelIf("smartModel_0")->render();
}


void Init::InitDefault::registerClass()
{
	std::cout << "registerClass function called!" << std::endl;

	// 1] Register Constructor (Class)
	REGISTER_CLASS(Model::StaticModel);
	REGISTER_CLASS(Mesh::DefaultMesh);
	REGISTER_CLASS(Shader::DefaultShader);

	REGISTER_CLASS(Loader::ModelLoader);
	REGISTER_CLASS(Loader::TextureLoader);
	REGISTER_CLASS(GPUObject::ModelGPUObject);
	REGISTER_CLASS(GPUObject::TextureGPUObject);

	Common::Factory::getInstance().showMeSeededClasses();
}


void Init::InitDefault::createShaders()
{
	Common::Error err;

	std::shared_ptr<Shader::DefaultShader> smartShader_0((Shader::DefaultShader*)Common::Factory::getInstance().constructObject("Shader::DefaultShader", err, "smartShader_0"));
	Common::Factory::getInstance().storeInContainer("ShaderIf", smartShader_0);


	std::cout << " xxx SHOW ME SHADERS xxx" << '\n';
	Common::Factory::getInstance().showMeObjects("ShaderIf");
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

	std::cout << " xxx SHOW ME MESHEs xxx" << '\n';
	Common::Factory::getInstance().showMeObjects("MeshIf");
}


// Create MODELs
void Init::InitDefault::createLoaders()
{
	Common::Error err;

	std::shared_ptr<Loader::ModelLoader> modelLoader_0( (Loader::ModelLoader*)Common::Factory::getInstance().constructObject("Loader::ModelLoader", err, "modelLoader_0") );
	Common::Factory::getInstance().storeInContainer("LoaderIf", modelLoader_0);

	std::shared_ptr<Loader::TextureLoader> textureLoader_0((Loader::TextureLoader*)Common::Factory::getInstance().constructObject("Loader::TextureLoader", err, "textureLoader_0"));
	Common::Factory::getInstance().storeInContainer("LoaderIf", textureLoader_0);

	std::cout << " xxx SHOW ME LOADERs xxx" << '\n';
	Common::Factory::getInstance().showMeObjects("LoaderIf");
}


void Init::InitDefault::createModels()
{
	Common::Error err;
	// Create                                                                                                             Model::StaticModel"       .. /modelPath/    smartModel_0
	// Model object
	std::shared_ptr<Model::StaticModel> smartModel_0((Model::StaticModel*)Common::Factory::getInstance().constructObject("Model::StaticModel", err, "smartModel_0"));
	Common::Factory::getInstance().storeInContainer("ModelIf", smartModel_0);

	std::cout << " xxx SHOW ME MODELSs xxx" << '\n';
	Common::Factory::getInstance().showMeObjects("ModelIf");
}