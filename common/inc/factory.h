#pragma once
#include <map>  
#include <string>  
#include <memory>  
#include <vector>  

#include "database.h"
#include "error.h"
#include "log.h"

#include "controlIf.h"
#include "controlDefault.h"

#include "cameraIf.h"
#include "cameraDefault.h"

#include "lightIf.h"
#include "lightDefault.h"

#include "loaderIf.h"
#include "modelLoader.h"
#include "textureLoader.h"

#include "gpuObjectIf.h"
#include "modelGPUObject.h"
#include "textureGPUObject.h"

#include "modelIf.h"
#include "staticModel.h"
#include "terrainModel.h"

#include "shaderIf.h"
#include "defaultShader.h"
#include "normalMapShader.h"
#include "terrainShader.h"

// Map in class members (ClassName, constructorPtr(const str&, const str&)
// Register class in map with registerClassNew method
#define REGISTER_CLASS_NEW(ConstructorName) Common::Factory::getInstance().registerClassNew<ConstructorName>(#ConstructorName)

/*
Factory:
Class Registration
- Class registration (insert in map)

Object Creation
- Create object (find in map and create instance)

Other
- Error, Log, Database
*/

namespace Common
{
/*! @brief Method for object construction
*   @param objectName Name (ID) of particaular instance
*   @return void pointer on particular created object
*/
// - Constructor type (const str&, const str&)
// arg0 - instanceDbPath (without instance name)
// arg1 - instanceName
template <class T> void* constructorNew(const std::string& arg0, const std::string& arg1)
{
	return (void*)new T(arg0, arg1);
}


class Factory
{
public:
	/*! @brief Get singleton factory instance
	*   @return Factory reference 
	*/
	static Factory& getInstance()
	{
		static Factory instance;
		return instance;
	}

	~Factory() {};

	Factory(Factory const&) = delete;
	void operator=(Factory const&) = delete;

	/*! @brief Method for class registration - map(constructor name, constructor pointer)
	*   @param constructorName Namespace::constructorName
	*   @return void
	*/
	// - ConstructorName (ex: Model::StaticModel) 
	template <class T>
	void registerClassNew(std::string const& constructorName)
	{
		m_classesMapNew.insert(std::make_pair(constructorName, &constructorNew<T>));
	}
	/*! @brief Method for object creation
	*   @param constructorName Namespace::constructorName
	*   @param arg0 object name
	*   @return void
	*/
	// - Find constructor pointer with constructorName and create object using that constructor pointer
	void* constructObjectNew(std::string const& constructorName, const std::string& arg0, const std::string& arg1)
	{
		mapTypeNew::iterator i = m_classesMapNew.find(constructorName);
		if (i == m_classesMapNew.end()) return 0; // or throw or whatever you want  
		return i->second(arg0, arg1);
	}

	void preInit()
	{
		// Create global Error object
		m_error = std::make_unique<Common::Error>();
		// Create global Log object
		m_log = std::make_unique<Common::Log>("log_0");

		registerClass();
	}


	void postInit()
	{
	}


	/*! @brief Set database object created from init object (during init phase)
	*   @param database
	*   @return void
	*/
	void setDatabase(std::unique_ptr<Common::Database>& database)
	{
		m_database = std::move(database);
	}


	/*! @brief Get reference on global database object
     *  @return reference on database object
     */
	std::unique_ptr<Common::Database>& getDatabase()
	{
		return m_database;
	}


	/*! @brief Get reference on global error object
	 *  @return reference on error object
	 */
	std::unique_ptr<Common::Error>& getErrorObject()
	{
		return m_error;
	}


	/*! @brief Get reference on global log object
	 *  @param -
	 *  @return reference on log object
	 */
	std::unique_ptr<Common::Log>& getLog()
	{
		return m_log;
	}


	/*! @brief Register class using MACRO - Generator of objects
     *  @return void
     */
	void registerClass()
	{
		// ControlIf
		REGISTER_CLASS_NEW(Control::ControlDefault);

		// CameraIf
	    REGISTER_CLASS_NEW(Camera::CameraDefault);

		// LightIf
		REGISTER_CLASS_NEW(Light::LightDefault);

		// ----
		// LoaderIf
		REGISTER_CLASS_NEW(Loader::ModelLoader);
		REGISTER_CLASS_NEW(Loader::TextureLoader);
		// ----

		// ModelIf
		REGISTER_CLASS_NEW(Model::StaticModel);
		REGISTER_CLASS_NEW(Model::TerrainModel);

		// ShaderIf
		REGISTER_CLASS_NEW(Shader::DefaultShader);
		REGISTER_CLASS_NEW(Shader::NormalMapShader);
		REGISTER_CLASS_NEW(Shader::TerrainShader);
	}


	/*! @brief Create objects from DB
	 *  @return void
	 */
	void createObjects()
	{
		std::cout << " [CREATING OBJECTs] ";
		createAllClusters();

		std::cout << '\n';
	}


	void createAllClusters()
	{
		std::string clusters("clusters");
		std::vector<std::string> vecOfClustersStrings;

		// DB: clusters    string    controls cameras lights loaders models shaders ...
		FACTORY.getDatabase()->getStringsFromDB(clusters, vecOfClustersStrings);
		for (auto s : vecOfClustersStrings)
		{
			createModels(s);
		}
	}

	void createModels(const std::string& cluster)
	{   
		std::string dbPath1 = cluster;
		std::vector<std::string> vecOfModelsStrings;

		// DB ex: models    string    staticModel terrainModel ...
		FACTORY.getDatabase()->getStringsFromDB(dbPath1, vecOfModelsStrings);

		for (auto s : vecOfModelsStrings)
		{
			// dB ex: instanceDbPath: "models_staticModel_"
			std::string instanceDbPath = dbPath1 + "_" + s + "_"; // arg0 of constructor - Instance dB locator

			std::string constructorNameDbPath = dbPath1 + "_" + s + "_" + "constructorName";
			std::vector<std::string> vecOfConstructorString;
			// ex vecOfConstructorString[0]: "Model::StaticModel"
			FACTORY.getDatabase()->getStringsFromDB(constructorNameDbPath, vecOfConstructorString);

			std::string instanceNameDbPath = dbPath1 + "_" + s + "_" + "instanceNames";
			std::vector<std::string> vecOfInstanceString;
			// ex vecOfInstanceString: "vanquish"
			FACTORY.getDatabase()->getStringsFromDB(instanceNameDbPath, vecOfInstanceString);

			// Create each instance
			// ex: vanquish ...
			for (auto s : vecOfInstanceString)
			{
				if (!dbPath1.compare("controls"))
				{
					std::shared_ptr<Control::ControlIf> control((Control::ControlIf*)constructObjectNew(vecOfConstructorString[0], instanceDbPath, s));
					control->preInitialization();

					storeInContainer("ControlIf", control); 
					std::cout << ".";
				}
				else if (!dbPath1.compare("cameras"))
				{
					std::shared_ptr<Camera::CameraIf> camera((Camera::CameraIf*)constructObjectNew(vecOfConstructorString[0], instanceDbPath, s));
					camera->preInitialization();

					storeInContainer("CameraIf", camera); 
					std::cout << ".";
				}
				else if (!dbPath1.compare("lights"))
				{
					std::shared_ptr<Light::LightIf> light((Light::LightIf*)constructObjectNew(vecOfConstructorString[0], instanceDbPath, s));
					light->preInitialization();
					
					storeInContainer("LightIf", light); 
					std::cout << ".";
				}
				else if (!dbPath1.compare("loaders"))
				{
					std::shared_ptr<Loader::LoaderIf> loader((Loader::LoaderIf*)constructObjectNew(vecOfConstructorString[0], instanceDbPath, s));
					loader->preInitialization();

					storeInContainer("LoaderIf", loader); 
					std::cout << ".";
				}
				else if (!dbPath1.compare("models"))
				{
					std::shared_ptr<Model::ModelIf> model((Model::ModelIf*)constructObjectNew(vecOfConstructorString[0], instanceDbPath, s));					
					model->preInitialization();

					storeInContainer("ModelIf", model);
					std::cout << ".";
				}
				else if (!dbPath1.compare("shaders"))
				{
					std::shared_ptr<Shader::ShaderIf> shader((Shader::ShaderIf*)constructObjectNew(vecOfConstructorString[0], instanceDbPath, s));
					shader->preInitialization();

					storeInContainer("ShaderIf", shader);
					std::cout << ".";
				}
				else 
				{					
				}
			}
		}
	}


	/*! @brief Show classes registered in map m_classesMap(constructorName, construcor pointer)
	 *  @return void
	 */
	void showMeSeededClasses()
	{
		mapTypeNew::iterator it;
		for (it = m_classesMapNew.begin(); it != m_classesMapNew.end(); ++it)
		{
			std::cout << " - " << it->first << "\n";
		}
	}


	/*! @brief Show all objects generated from classes within one interface
	 *  @return void
	 */
	void showMeObjects(const std::string& objNameIf)
	{
		if (!objNameIf.compare("ControlIf"))
		{
			printName(m_vecOfControlIf);
		}
		else if (!objNameIf.compare("CameraIf"))
		{
			printName(m_vecOfCameraIf);
		}
		else if (!objNameIf.compare("LightIf"))
		{
			printName(m_vecOfLightIf);
		}
		// ----
		else if (!objNameIf.compare("LoaderIf"))
		{
			printName(m_vecOfLoaderIf);
		}
		// ----
		else if (!objNameIf.compare("GPUObjectIf"))
		{
			printName(m_vecOfGPUObjectIf);
		}
		else if (!objNameIf.compare("ModelIf"))
		{
			printName(m_vecOfModelIf);
		}
		else if (!objNameIf.compare("ShaderIf"))
		{
			printName(m_vecOfShaderIf);
		}
		else
		{
			// Print something ... msg
		}
	}
	
	template<class T>
	void printName(T& vec0)
	{
		for (auto it = vec0.begin(); it != vec0.end(); ++it)
		{
			std::cout << (*it)->getName() << '\n';
		}
	}

	// TODO: Remove Template setter (store)
	void storeInContainer(const std::shared_ptr<GPUObject::MeshStructure>& meshStruct)
	{
		m_vecOfMeshStructure.push_back(meshStruct);
	}

	void storeInContainer(const std::shared_ptr<GPUObject::RawTextureStructure>& rawTextureStruct)
	{
		m_vecOfRawTextureStructure.push_back(rawTextureStruct);
	}

	/*! @brief Store object in container
	 *  @param - objNameIf
	 *  @param - derivedObject
	 *  @return void
	 */
	template<class T>
	void storeInContainer(const std::string& objNameIf, const T& derivedObject)
	{
		if (!objNameIf.compare("ControlIf"))
		{
			m_vecOfControlIf.push_back(std::dynamic_pointer_cast<Control::ControlIf>(derivedObject));
		}
		else if (!objNameIf.compare("CameraIf"))
		{
		    m_vecOfCameraIf.push_back(std::dynamic_pointer_cast<Camera::CameraIf>(derivedObject));
		}
		else if (!objNameIf.compare("LightIf"))
		{
			m_vecOfLightIf.push_back(std::dynamic_pointer_cast<Light::LightIf>(derivedObject));
		}
		// ----
		else if (!objNameIf.compare("LoaderIf"))
		{
			m_vecOfLoaderIf.push_back(std::dynamic_pointer_cast<Loader::LoaderIf>(derivedObject));
		}
		// ----
		else if (!objNameIf.compare("GPUObjectIf"))
		{
			m_vecOfGPUObjectIf.push_back(std::dynamic_pointer_cast<GPUObject::GPUObjectIf>(derivedObject));
		}
		else if (!objNameIf.compare("ModelIf"))
		{
			m_vecOfModelIf.push_back(std::dynamic_pointer_cast<Model::ModelIf>(derivedObject));
		}
		else if (!objNameIf.compare("ShaderIf"))
		{
			m_vecOfShaderIf.push_back(std::dynamic_pointer_cast<Shader::ShaderIf>(derivedObject));
		}
		else
		{
			// FACTORY.getErrorObject()->setError("ERROR: " + objNameIf + " can not be found!");
			// FACTORY.getLog()->LOGFILE(LOG "ERROR: " + objNameIf + " can not be found!");
		}
	}


	// GET object - TODO: Make this generic
	/*! @brief get object (within particaulary interface) from container
	 *  @param - objNameIf
	 *  @param - derivedObject
	 *  @return void
	 */
	// -- Get Controls via Interface --
	std::vector<std::shared_ptr<Control::ControlIf>>& getControlIfVec()
	{
		return m_vecOfControlIf;
	}
	std::shared_ptr<Control::ControlIf>& getControlIf(const std::string& arg0)
	{
		return getObjectFromVec(m_vecOfControlIf, arg0);
	}
	// ----

	// -- Cameras --
	std::vector<std::shared_ptr<Camera::CameraIf>>& getCameraIfVec()
	{
		return m_vecOfCameraIf;
	}
	std::shared_ptr<Camera::CameraIf>& getCameraIf(const std::string& arg0)
	{
		return getObjectFromVec(m_vecOfCameraIf, arg0);
	}
	// ----

	// -- Lights --
	std::vector<std::shared_ptr<Light::LightIf>>& getLightIfVec()
	{
		return m_vecOfLightIf;
	}
	std::shared_ptr<Light::LightIf>& getLightIf(const std::string& arg0)
	{
		return getObjectFromVec(m_vecOfLightIf, arg0);
	}
	// ----

	// -- Loaders --
	std::vector<std::shared_ptr<Loader::LoaderIf>>& getLoaderIfVec()
	{
		return m_vecOfLoaderIf;
	}
	std::shared_ptr<Loader::LoaderIf>& getLoaderIf(const std::string& arg0)
	{
		return getObjectFromVec(m_vecOfLoaderIf, arg0);
	}
	// ----

	// -- GPUObjects --
	std::vector<std::shared_ptr<GPUObject::GPUObjectIf>>& getGPUObjectIfVec()
	{
		return m_vecOfGPUObjectIf;
	}
	std::shared_ptr<GPUObject::GPUObjectIf>& getGPUObjectIf(const std::string& arg0)
	{
		return getObjectFromVec(m_vecOfGPUObjectIf, arg0);
	}
	// ----

	// -- Model --
	std::vector<std::shared_ptr<Model::ModelIf>>& getModelIfVec()
	{
		return m_vecOfModelIf;
	}
	std::shared_ptr<Model::ModelIf>& getModelIf(const std::string& arg0)
	{
		return getObjectFromVec(m_vecOfModelIf, arg0);
	}
	// ----

	// -- Shader --
	std::vector<std::shared_ptr<Shader::ShaderIf>>& getShaderIfVec()
	{
		return m_vecOfShaderIf;
	}
	std::shared_ptr<Shader::ShaderIf>& getShaderIf(const std::string& arg0)
	{
		return getObjectFromVec(m_vecOfShaderIf, arg0);
	}
	// ----

	// -- Loaders stuff --
	std::shared_ptr<GPUObject::MeshStructure>& getMeshStructure(const std::string& arg0)
	{
		return getObjectFromVec(m_vecOfMeshStructure, arg0);
	}

	std::shared_ptr<GPUObject::RawTextureStructure>& getRawTextureStructure(const std::string& arg0)
	{
		return getObjectFromVec(m_vecOfRawTextureStructure, arg0);
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

		// If not found, return something
		std::cout << " NOT FOUND: " << arg1 << " Returning: " << vec0[0]->getName() << '\n';
		return vec0[0];
	}


private:	
	// Singleton Factory - Private Constructor
	Factory() 
	{
	};

	// Factory Stuff 
	// - Create map(ConstructorName, constructorPtr) constructorPtr(str, str)
	typedef void* (*constructor_NEW)(const std::string&, const std::string&);
	typedef std::map<std::string, constructor_NEW> mapTypeNew;
	mapTypeNew m_classesMapNew;

	// DataBase
	std::unique_ptr<Common::Database> m_database;
	// Error
	std::unique_ptr<Common::Error> m_error;
	// Log
	std::unique_ptr<Common::Log> m_log;


	// Container Stuff
	std::vector<std::shared_ptr<Control::ControlIf>>     m_vecOfControlIf;

	std::vector<std::shared_ptr<Camera::CameraIf>>       m_vecOfCameraIf;
	std::vector<std::shared_ptr<Light::LightIf>>         m_vecOfLightIf;
	// ----
	std::vector<std::shared_ptr<Loader::LoaderIf>>       m_vecOfLoaderIf;
	// ----
	std::vector<std::shared_ptr<GPUObject::GPUObjectIf>> m_vecOfGPUObjectIf;

	std::vector<std::shared_ptr<Model::ModelIf>>         m_vecOfModelIf;
	std::vector<std::shared_ptr<Shader::ShaderIf>>       m_vecOfShaderIf;

	// ----
	std::vector<std::shared_ptr<GPUObject::MeshStructure>>       m_vecOfMeshStructure;
	std::vector<std::shared_ptr<GPUObject::RawTextureStructure>> m_vecOfRawTextureStructure;
};
} // End of namespace