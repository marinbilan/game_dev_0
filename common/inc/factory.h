#pragma once
#include <map>  
#include <string>  
#include <iostream>  
#include <memory>  
#include <vector>  

#include "database.h"
#include "error.h"
#include "log.h"

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


#define REGISTER_CLASS(ConstructorName) Common::Factory::getInstance().registerClass<ConstructorName>(#ConstructorName)

namespace Common
{

// ---- Constructor Prototype ---- 
template <class T> void* constructor(Error& err, const std::string& arg0)
{
	return (void*)new T(err, arg0);
}

// ---- Factroy ---- 
class Factory
{
public:
	// Singleton "constructor"
	static Factory& getInstance()
	{
		static Factory instance;
		return instance;
	}

	Factory(Factory const&) = delete;
	void operator=(Factory const&) = delete;

	~Factory() {};
	//
	// ---- xx START xx ----
	// 1] Type of constructor  (two args - Error&, std::string)  
	template <class T>
	void registerClass(std::string const& ConstructorName)
	{
		m_classesMap.insert(std::make_pair(ConstructorName, &constructor<T>));
	}

	// 2] Construct object out of seed - Get constructor (map - second) and create object with params  
	void* constructObject(std::string const& constructorName, Error& err, const std::string& arg0)
	{
		mapType::iterator i = m_classesMap.find(constructorName);
		if (i == m_classesMap.end()) return 0; // or throw or whatever you want  
		return i->second(err, arg0);
	}
	// ---- xx END xx ----


	// ---------
	// FUNCTIONS
	// ---------
	void preInit()
	{
		// Create "global" objects
		// Error
		m_error = std::make_unique<Common::Error>();
		// Log
		m_log = std::make_unique<Common::Log>("log_0");


		// Register Class
		registerClass();

		// Create Objects
		createObjects();
	}


	void postInit()
	{

	}


	// ---------
    // DATABASE
    // ---------
	void setDatabase(std::unique_ptr<Common::Database>& database)
	{
		m_database = std::move(database);
	}

	std::unique_ptr<Common::Database>& getDatabase()
	{
		return m_database;
	}
	// --------


	// -----
	// ERROR
	// -----
	std::unique_ptr<Common::Error>& getErrorObject()
	{
		return m_error;
	}
	// --------





	void registerClass()
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


	// ----------------------------
	// CREATE OBJECTS FROM DATABASE
	// ----------------------------

	void createObjects()
	{
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


	void createObjects(const std::string& name_space, const std::string& inter_face)
	{
		Common::Error err;

		std::vector<std::string> vecArg0;
		std::vector<std::string> vecArg1;

		// GET ALL DERIVED CLASSes FROM SAME IF
		Common::Factory::getInstance().getDatabase()->create("Create", inter_face, vecArg0, vecArg1);

		// Iterate over colums and create objects with the same interface
		// vecArg0 - vector (column) of derived classes
		// vecArg1 - vector (column) of derived classes names
		auto it1 = vecArg1.begin();
		for (auto it0 = vecArg0.begin(); it0 != vecArg0.end(); ++it0)
		{
			if (!inter_face.compare("CameraIf"))
			{
				std::shared_ptr<Camera::CameraIf> camera((Camera::CameraIf*)constructObject(name_space + *it0, err, *it1));
				storeInContainer(inter_face, camera);
			}
			else if (!inter_face.compare("MeshIf"))
			{
				std::shared_ptr<Mesh::MeshIf> mesh((Mesh::MeshIf*)constructObject(name_space + *it0, err, *it1));
				storeInContainer(inter_face, mesh);
			}
			else if (!inter_face.compare("LoaderIf"))
			{
				std::shared_ptr<Loader::LoaderIf> loader((Loader::LoaderIf*)constructObject(name_space + *it0, err, *it1));
				storeInContainer(inter_face, loader);
			}
			else if (!inter_face.compare("ModelIf"))
			{
				std::shared_ptr<Model::ModelIf> model((Model::ModelIf*)constructObject(name_space + *it0, err, *it1));
				storeInContainer(inter_face, model);
			}
			else if (!inter_face.compare("ShaderIf"))
			{
				std::shared_ptr<Shader::ShaderIf> shader((Shader::ShaderIf*)constructObject(name_space + *it0, err, *it1));
				storeInContainer(inter_face, shader);
			}

			++it1;
		}
	}
	// --------


	// ---- [0] ---- 
	void showMeSeededClasses()
	{
		mapType::iterator it;
		for (it = m_classesMap.begin(); it != m_classesMap.end(); ++it)
		{
			std::cout << " - " << it->first << "\n";
		}
	}


	// ---- [1] ---- 
	void showMeObjects(const std::string& objNameIf)
	{
		if (!objNameIf.compare("LoaderIf"))
		{
			printName(m_vecOfLoaderIf);
		}
		else if (!objNameIf.compare("GPUObjectIf"))
		{
			printName(m_vecOfGPUObjectIf);
		}
		else if (!objNameIf.compare("ModelIf"))
		{
			printName(m_vecOfModelIf);
		}
		else if (!objNameIf.compare("MeshIf"))
		{
			printName(m_vecOfMeshIf);
		}
		else if (!objNameIf.compare("ShaderIf"))
		{
			printName(m_vecOfShaderIf);
		}
		else if (!objNameIf.compare("CameraIf"))
		{
			printName(m_vecOfCameraIf);
		}
		else
		{
			std::cout << "ERROR: objNameIf can not be found!" << '\n';
		}
	}
	// Generic Object Name Printer
	template<class T>
	void printName(T& vec0)
	{
		for (auto it = vec0.begin(); it != vec0.end(); ++it)
		{
			std::cout << "- PRINT NAME TEST -" << (*it)->getName() << '\n';
		}
	}


	// SET - Store
	// ---- [2] ---- 
	template<class T>
	// args 1] classIf    2] derived objectName
	void storeInContainer(const std::string& objNameIf, const T& derivedObject)
	{
		// CameraIf
		if (!objNameIf.compare("CameraIf"))
		{
		m_vecOfCameraIf.push_back(std::dynamic_pointer_cast<Camera::CameraIf>(derivedObject));
		}
		// LoaderIf
		else if (!objNameIf.compare("LoaderIf"))
		{
			m_vecOfLoaderIf.push_back(std::dynamic_pointer_cast<Loader::LoaderIf>(derivedObject));
		}
		// GPUObjectIf
		else if (!objNameIf.compare("GPUObjectIf"))
		{
			m_vecOfGPUObjectIf.push_back(std::dynamic_pointer_cast<GPUObject::GPUObjectIf>(derivedObject));
		}
		// ModelIf
		else if (!objNameIf.compare("ModelIf"))
		{
			m_vecOfModelIf.push_back(std::dynamic_pointer_cast<Model::ModelIf>(derivedObject));
		}
		// MeshIf
		else if (!objNameIf.compare("MeshIf"))
		{
			m_vecOfMeshIf.push_back(std::dynamic_pointer_cast<Mesh::MeshIf>(derivedObject));
		}
		// ShaderIf
		else if (!objNameIf.compare("ShaderIf"))
		{
			m_vecOfShaderIf.push_back(std::dynamic_pointer_cast<Shader::ShaderIf>(derivedObject));
		}
		else
		{
			std::cout << "ERROR: Can not store derivedObject in container" << "\n";
		}
	}


	// GET object - TODO: Make this generic
	// ---- [3] ---- 
	// ADD INTERFACE 
	std::shared_ptr<Camera::CameraIf>& getCameraIf(const std::string& arg0)
	{
		return getObjectFromVec(m_vecOfCameraIf, arg0);
	}

	std::shared_ptr<Loader::LoaderIf>& getLoaderIf(const std::string& arg0)
	{
		return getObjectFromVec(m_vecOfLoaderIf, arg0);
	}

	std::shared_ptr<GPUObject::GPUObjectIf>& getGPUObjectIf(const std::string& arg0)
	{
		return getObjectFromVec(m_vecOfGPUObjectIf, arg0);
	}

	std::shared_ptr<Model::ModelIf>& getModelIf(const std::string& arg0)
	{
		return getObjectFromVec(m_vecOfModelIf, arg0);
	}

	std::shared_ptr<Mesh::MeshIf>& getMeshIf(const std::string& arg0)
	{
		return getObjectFromVec(m_vecOfMeshIf, arg0);
	}

	std::shared_ptr<Shader::ShaderIf>& getShaderIf(const std::string& arg0)
	{
		return getObjectFromVec(m_vecOfShaderIf, arg0);
	}

	// Generic getter 
	template<class T>
	auto getObjectFromVec(T& vec0, const std::string& arg1) -> decltype(vec0.at(0))
	{
		for (auto it = vec0.begin(); it != vec0.end(); ++it)
		{
			if (!(*it)->getName().compare(arg1))
			{
				return *it;
			}
		}

		// If can't find element in vector, return first
		std::cout << "ERROR: Can not find element in vector! " << '\n';
		return vec0[0];
	}

private:	
	// Singleton Factory - Constructor private
	Factory() 
	{
	};
	//
	// Factory Stuff 
	//
	typedef void*(*constructor_t)(Error&, const std::string&);
	typedef std::map<std::string, constructor_t> mapType;
	mapType m_classesMap;
	//
	// DataBase
	std::unique_ptr<Common::Database> m_database;
	// Error
	std::unique_ptr<Common::Error> m_error;
	// Log
	std::unique_ptr<Common::Log> m_log;

	//
	// Container Stuff 
	//
	std::vector<std::shared_ptr<Camera::CameraIf>>       m_vecOfCameraIf;

	std::vector<std::shared_ptr<Loader::LoaderIf>>       m_vecOfLoaderIf;
	std::vector<std::shared_ptr<GPUObject::GPUObjectIf>> m_vecOfGPUObjectIf;

	std::vector<std::shared_ptr<Model::ModelIf>>         m_vecOfModelIf;
	std::vector<std::shared_ptr<Mesh::MeshIf>>           m_vecOfMeshIf;
	std::vector<std::shared_ptr<Shader::ShaderIf>>       m_vecOfShaderIf;
};
} // End of namespace
 