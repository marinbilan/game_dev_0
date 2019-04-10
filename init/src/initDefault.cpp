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
	createModels();
	createMeshes();
	createShaders();
	createLoaders();

	// Test
	std::cout << " NUM OF INSTANCES after LOADER: " << Common::Factory::getInstance().getGPUObjectIf("vanquish").use_count() << "\n";
}


void Init::InitDefault::postInit()
{
	std::cout << "postInit function called!" << std::endl;

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


void Init::InitDefault::createModels()
{	
	// 2] FIND in MAP (first) seeded objects - and - INSTANTIATE OBJECT (second) 
	Common::Error err;
	// Create                                                                                                             Model::StaticModel"       .. /modelPath/    smartModel_0
	// Model object
	std::shared_ptr<Model::StaticModel> smartModel_0((Model::StaticModel*)Common::Factory::getInstance().constructObject("Model::StaticModel", err, "smartModel_0"));
	Common::Factory::getInstance().storeInContainer("ModelIf", smartModel_0);


	// Test
	// std::shared_ptr<Model::ModelIf> smartModel_1 = Common::Factory::getInstance().getModelIf("smartModel_0");	
}


void Init::InitDefault::createMeshes()
{
	Common::Error err;
	std::shared_ptr<Mesh::DefaultMesh> smartMesh_0((Mesh::DefaultMesh*)Common::Factory::getInstance().constructObject("Mesh::DefaultMesh", err, "smartMesh_0"));
	Common::Factory::getInstance().storeInContainer("MeshIf", smartMesh_0);
}


void Init::InitDefault::createShaders()
{
	Common::Error err;

	std::shared_ptr<Shader::DefaultShader> smartShader_0((Shader::DefaultShader*)Common::Factory::getInstance().constructObject("Shader::DefaultShader", err, "smartShader_0"));
	Common::Factory::getInstance().storeInContainer("ShaderIf", smartShader_0);
	std::shared_ptr<Shader::DefaultShader> smartShader_1((Shader::DefaultShader*)Common::Factory::getInstance().constructObject("Shader::DefaultShader", err, "smartShader_1"));
	Common::Factory::getInstance().storeInContainer("ShaderIf", smartShader_1);
}


// Create MODELs
void Init::InitDefault::createLoaders()
{
	Common::Error err;

	// Create TEMP ModelLoader and Create all GPUModelObjects
	std::shared_ptr<Loader::ModelLoader> modelLoader_0( (Loader::ModelLoader*)Common::Factory::getInstance().constructObject("Loader::ModelLoader", err, "modelLoader_0") );
	// Common::Factory::getInstance().storeInContainer("LoaderIf", modelLoader_0);

	// std::cout << " NUM OF INSTANCES after LOADER: " << Common::Factory::getInstance().getGPUObjectIf("vanquish").use_count() << "\n";
	Common::Factory::getInstance().getGPUObjectIf("vanquish")->info();

	std::shared_ptr<Loader::TextureLoader> textureLoader_0((Loader::TextureLoader*)Common::Factory::getInstance().constructObject("Loader::TextureLoader", err, "textureLoader_0"));
	// Common::Factory::getInstance().storeInContainer("LoaderIf", textureLoader_0);

}