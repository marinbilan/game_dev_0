#include "initDefault.h"
#include "error.h"
#include "factory.h"
#include "modelIf.h"
#include "staticModel.h"
#include "meshIf.h"
#include "defaultMesh.h"


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
	
	registerClass();

	createDefaultObject();
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

	// defaultFactory.showMeSeededClasses();
	Common::Factory::getInstance().showMeSeededClasses();
	

}


void Init::InitDefault::createDefaultObject()
{
	std::cout << "createDefaultObject function called!" << std::endl;

	
	// 2] FIND in MAP (first) seeded objects - and - INSTANTIATE OBJECT (second) 
	// Function  
	Common::Error err;
	// Create                                                                                                             Model::StaticModel"       .. /modelPath/    smartModel_0
	// Model object
	std::shared_ptr<Model::StaticModel> smartModel_0((Model::StaticModel*)Common::Factory::getInstance().constructObject("Model::StaticModel", err, "smartModel_0"));
	// Mesh object
	std::shared_ptr<Mesh::DefaultMesh> smartMesh_0((Mesh::DefaultMesh*)Common::Factory::getInstance().constructObject("Mesh::DefaultMesh", err, "smartMesh_0"));
	
	
	// Store Model object
	Common::Factory::getInstance().storeInContainer(smartModel_0);
	Common::Factory::getInstance().storeInContainer(smartMesh_0);


	//
	// Common::Factory::getInstance().showMeCommonIfObjects();

	// Test
	// std::shared_ptr<Model::ModelIf> smartModel_1 = Common::Factory::getInstance().getModelIf("smartModel_0");
	
}
