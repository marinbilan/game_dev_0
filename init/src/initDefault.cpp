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

	// Create Cameras
	createObjects("Camera::", "CameraIf");

	// Create Meshes
	createObjects("Mesh::", "MeshIf");

	// Create Loaders
	createObjects("Loader::", "LoaderIf");

	// Create Models
	createObjects("Model::", "ModelIf");

	// Create Shaders
	createObjects("Shader::", "ShaderIf");
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


void Init::InitDefault::registerClass()
{
	std::cout << "registerClass function called!" << std::endl;

	// 1] Register Constructor (Class)
	//
	// CameraIf
	REGISTER_CLASS(Camera::CameraDefault);
	
	// LoaderIf
	REGISTER_CLASS(Loader::ModelLoader);
	REGISTER_CLASS(Loader::TextureLoader);

	// GPUObjectIf
	REGISTER_CLASS(GPUObject::TextureGPUObject);
	REGISTER_CLASS(GPUObject::ModelGPUObject);

	// ModelIf
	REGISTER_CLASS(Model::StaticModel);

	// MeshIf
	REGISTER_CLASS(Mesh::DefaultMesh);

	// ShaderIf
	REGISTER_CLASS(Shader::DefaultShader);

	Common::Factory::getInstance().showMeSeededClasses();
}


void Init::InitDefault::createObjects(const std::string& name_space, const std::string& inter_face)
{
	Common::Error err;

	std::vector<std::string> vecArg0;
	std::vector<std::string> vecArg1;

	// String Variables
	// std::string Create("Create");
	// std::string CameraIf("CameraIf");

	// Get this from Factory
	Common::Factory::getInstance().getDatabase()->create("Create", inter_face, vecArg0, vecArg1);

	// Iterate over colums and create objects with the same interface
	// vecArg0 - vector (column) of derived classes
	// vecArg1 - vector (column) of derived classes names
	auto it1 = vecArg1.begin();
	for (auto it0 = vecArg0.begin(); it0 != vecArg0.end(); ++it0)
	{
		if(!inter_face.compare("CameraIf"))
		{
			std::shared_ptr<Camera::CameraIf> camera((Camera::CameraIf*)Common::Factory::getInstance().constructObject(name_space + *it0, err, *it1));
			Common::Factory::getInstance().storeInContainer(inter_face, camera);
		}
		else if (!inter_face.compare("MeshIf"))
		{
			std::shared_ptr<Mesh::MeshIf> mesh((Mesh::MeshIf*)Common::Factory::getInstance().constructObject(name_space + *it0, err, *it1));
			Common::Factory::getInstance().storeInContainer(inter_face, mesh);
		}
		else if (!inter_face.compare("LoaderIf"))
		{
			std::shared_ptr<Loader::LoaderIf> loader((Loader::LoaderIf*)Common::Factory::getInstance().constructObject(name_space + *it0, err, *it1));
			Common::Factory::getInstance().storeInContainer(inter_face, loader);
		}
		else if (!inter_face.compare("ModelIf"))
		{
			std::shared_ptr<Model::ModelIf> model((Model::ModelIf*)Common::Factory::getInstance().constructObject(name_space + *it0, err, *it1));
			Common::Factory::getInstance().storeInContainer(inter_face, model);
		}
		else if (!inter_face.compare("ShaderIf"))
		{
			std::shared_ptr<Shader::ShaderIf> shader((Shader::ShaderIf*)Common::Factory::getInstance().constructObject(name_space + *it0, err, *it1));
			Common::Factory::getInstance().storeInContainer(inter_face, shader);
		}

		++it1;
	}
}


