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

#define REGISTER_CLASS(ConstructorName) Common::Factory::getInstance().registerClass<ConstructorName>(#ConstructorName)

/*
Factory:
Class Registration
1] class registration (insert in map)

Object Creation
1] create object (find in map and create instance)

Other
1] Error, Log, Database
*/

namespace Common
{
/*! @brief Method for object construction
*   @param objectName Name (ID) of particaular instance
*   @return void pointer on particular created object
*/
template <class T> void* constructor(const std::string& objectName)
{
	return (void*)new T(objectName);
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
	template <class T>
	void registerClass(std::string const& constructorName)
	{
		m_classesMap.insert(std::make_pair(constructorName, &constructor<T>));
		// m_classesMapN.insert(std::make_pair(constructorName, &constructor<T>));
	}

	/*! @brief Method for object creation
	*   @param constructorName Namespace::constructorName
	*   @param arg0 object name
	*   @return void
	*/
	void* constructObject(std::string const& constructorName, const std::string& arg0)
	{
		mapType::iterator i = m_classesMap.find(constructorName);
		if (i == m_classesMap.end()) return 0; // or throw or whatever you want  
		return i->second(arg0);
	}

	// ========================================================================================
    // NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION
    // ========================================================================================
	void* constructObject(std::string const& constructorName, const std::string& arg0, const std::string& arg1)
	{
		mapTypeN::iterator i = m_classesMapN.find(constructorName);
		if (i == m_classesMapN.end()) return 0; // or throw or whatever you want  
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
		// CameraIf
		REGISTER_CLASS(Control::ControlDefault);

		// CameraIf
		REGISTER_CLASS(Camera::CameraDefault);

		// LightIf
		REGISTER_CLASS(Light::LightDefault);

		// ----
		// LoaderIf
		REGISTER_CLASS(Loader::ModelLoader);
		REGISTER_CLASS(Loader::TextureLoader);
		// ----

		// GPUObjectIf - Created by loaders (not DB driven)
		REGISTER_CLASS(GPUObject::ModelGPUObject);
		REGISTER_CLASS(GPUObject::TextureGPUObject);

		// ModelIf
		// ========================================================================================
		// NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION
		// ========================================================================================
		REGISTER_CLASS(Model::StaticModel);
		// 
		REGISTER_CLASS(Model::TerrainModel);

		// ShaderIf
		REGISTER_CLASS(Shader::DefaultShader);
		REGISTER_CLASS(Shader::NormalMapShader);
		REGISTER_CLASS(Shader::TerrainShader);
	}


	/*! @brief Create objects from DB
	 *  @return void
	 */
	void createObjects()
	{
		std::cout << " [CREATING OBJECTs] ";
		// Create Cameras
		createObjects("Control::", "ControlIf");

		// Create Cameras
		createObjects("Camera::", "CameraIf");

		// Create Lights
		createObjects("Light::", "LightIf");

		// ----
		// Create Loaders
		createObjects("Loader::", "LoaderIf");
		// ----

		// Create Models
		createObjects("Model::", "ModelIf");

		// Create Shaders
		createObjects("Shader::", "ShaderIf");

		// ========================================================================================
        // NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION
        // ========================================================================================
		createAllClusters();

		std::cout << '\n';
	}


	// ========================================================================================
    // NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION
    // ========================================================================================
	void createAllClusters()
	{
		std::string clusters("clusters");
		std::vector<std::string> vecOfClustersStrings;
		/*
			0st STAGE of creation
			db ex:
			clusters    string    models    somethingElse ...
		*/

		// vecOfClustersStrings: "models    somethingElse"
		Common::Factory::getInstance().getDatabase()->getStringsFromDB(clusters, vecOfClustersStrings);
		for (auto s : vecOfClustersStrings)
		{
			// std::cout << " CLUSTERS: " << s << '\n';
			createModels(s);
		}
	}
	void createModels(const std::string& cluster)
	{
		/*
	        1st STAGE of models creation - object tags
	        [dbPath]: models
	        db ex: 
			models    string    staticModel dynamicModels  otherModels ...
        */	    
		std::string dbPath1 = cluster;

		std::vector<std::string> vecOfModelsStrings;

		// vecOfModelsStrings: "staticModel dynamicModels  otherModels"
		Common::Factory::getInstance().getDatabase()->getStringsFromDB(dbPath1, vecOfModelsStrings);

		for (auto s : vecOfModelsStrings)
		{
			/*
	            2st STAGE of models creation - constructor and instanceNames
                ex [dbPath]: models_staticModel
                db ex:
				models_staticModel_constructorName    string    Model::StaticModel
                models_staticModel_instanceNames      string    vanquish
            */
			// dB ex:
			// instanceDbPath: "models_staticModel_"
			std::string instanceDbPath = dbPath1 + "_" + s + "_";

			std::string constructorNameDbPath = dbPath1 + "_" + s + "_" + "constructorName";
			std::string instanceNameDbPath = dbPath1 + "_" + s + "_" + "instanceNames";
			std::vector<std::string> vecOfConstructorString;
			std::vector<std::string> vecOfInstanceString;

			// vecOfConstructorString[0]: "Model::StaticModel"
			Common::Factory::getInstance().getDatabase()->getStringsFromDB(constructorNameDbPath, vecOfConstructorString);

			// vecOfInstanceString[0]: "vanquish ..."
			Common::Factory::getInstance().getDatabase()->getStringsFromDB(instanceNameDbPath, vecOfInstanceString);
			// foreach instanceNames
			for (auto s : vecOfInstanceString)
			{
				// std::cout << " Creating instance - Constructor: " << vecOfConstructorString[0] << " - InstanceName: " << s << " " << s.size() << '\n';

				if (!dbPath1.compare("models"))
				{
					std::shared_ptr<Model::ModelIf> model = std::make_shared<Model::StaticModel>(instanceDbPath, s);
					// TODO: remove
					model->preInitialization();
				}
				else {
					
				}
			}
		}

	}


	/*! @brief Create objects Namespace::ClassName, objectName
     *  @param - nameSpace
	 *  @param - interFace
     *  @return void
     */
	void createObjects(const std::string& nameSpace, const std::string& interFace)
	{
		Common::Error err;

		std::vector<std::string> vecClassNames;
		std::vector<std::string> vecObjectNames;

		// GET ALL DERIVED CLASSes FROM SAME IF
		Common::Factory::getInstance().getDatabase()->create("Create", interFace, vecClassNames, vecObjectNames);

		// Iterate over colums and create objects with the same interface
		// vecClassNames - vector (column) of derived classes
		// vecObjectNames - vector (column) of object names
		auto it1 = vecObjectNames.begin();
		for (auto it0 = vecClassNames.begin(); it0 != vecClassNames.end(); ++it0)
		{
			if (!interFace.compare("ControlIf"))
			{
				std::shared_ptr<Control::ControlIf> control((Control::ControlIf*)constructObject(nameSpace + *it0, *it1));
				storeInContainer(interFace, control);
				std::cout << ".";
			}
			if (!interFace.compare("CameraIf"))
			{
				std::shared_ptr<Camera::CameraIf> camera((Camera::CameraIf*)constructObject(nameSpace + *it0, *it1));
				storeInContainer(interFace, camera);
				std::cout << ".";
			}
			else if (!interFace.compare("LightIf"))
			{
				std::shared_ptr<Light::LightIf> light((Light::LightIf*)constructObject(nameSpace + *it0, *it1));
				storeInContainer(interFace, light);
				std::cout << ".";
			}
			// ----
			else if (!interFace.compare("LoaderIf"))
			{
				std::shared_ptr<Loader::LoaderIf> loader((Loader::LoaderIf*)constructObject(nameSpace + *it0, *it1));
				storeInContainer(interFace, loader);
				std::cout << ".";
			}
			// ----
			else if (!interFace.compare("ModelIf"))
			{
				std::shared_ptr<Model::ModelIf> model((Model::ModelIf*)constructObject(nameSpace + *it0, *it1));
				storeInContainer(interFace, model);
				std::cout << ".";
			}
			else if (!interFace.compare("ShaderIf"))
			{
				std::shared_ptr<Shader::ShaderIf> shader((Shader::ShaderIf*)constructObject(nameSpace + *it0, *it1));
				storeInContainer(interFace, shader);
				std::cout << ".";
			}

			++it1;
		}
	}


	/*! @brief Show classes registered in map m_classesMap(constructorName, construcor pointer)
	 *  @return void
	 */
	void showMeSeededClasses()
	{
		mapType::iterator it;
		for (it = m_classesMap.begin(); it != m_classesMap.end(); ++it)
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
	typedef void*(*constructor_t)(const std::string&);
	typedef std::map<std::string, constructor_t> mapType;
	mapType m_classesMap;

	// ========================================================================================
    // NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION
    // ========================================================================================
	typedef void* (*constructor_n)(const std::string&, const std::string&);
	typedef std::map<std::string, constructor_n> mapTypeN;
	mapTypeN m_classesMapN;

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