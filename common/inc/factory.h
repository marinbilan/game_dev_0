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


	void preInit()
	{
		// Create global Error object
		m_error = std::make_unique<Common::Error>();
		// Create global Log object
		m_log = std::make_unique<Common::Log>("log_0");

		registerClass();

		createObjects();
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
		REGISTER_CLASS(Camera::CameraDefault);

		// LoaderIf
		REGISTER_CLASS(Loader::ModelLoader);
		REGISTER_CLASS(Loader::TextureLoader);

		// GPUObjectIf
		REGISTER_CLASS(GPUObject::ModelGPUObject);
		REGISTER_CLASS(GPUObject::TextureGPUObject);

		// ModelIf
		REGISTER_CLASS(Model::StaticModel);

		// MeshIf
		REGISTER_CLASS(Mesh::DefaultMesh);

		// ShaderIf
		REGISTER_CLASS(Shader::DefaultShader);
	}


	/*! @brief Create objects from DB
	 *  @return void
	 */
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
			if (!interFace.compare("CameraIf"))
			{
				std::shared_ptr<Camera::CameraIf> camera((Camera::CameraIf*)constructObject(nameSpace + *it0, *it1));
				storeInContainer(interFace, camera);
			}
			else if (!interFace.compare("MeshIf"))
			{
				std::shared_ptr<Mesh::MeshIf> mesh((Mesh::MeshIf*)constructObject(nameSpace + *it0, *it1));
				storeInContainer(interFace, mesh);
			}
			else if (!interFace.compare("LoaderIf"))
			{
				std::shared_ptr<Loader::LoaderIf> loader((Loader::LoaderIf*)constructObject(nameSpace + *it0, *it1));
				storeInContainer(interFace, loader);
			}
			else if (!interFace.compare("ModelIf"))
			{
				std::shared_ptr<Model::ModelIf> model((Model::ModelIf*)constructObject(nameSpace + *it0, *it1));
				storeInContainer(interFace, model);
			}
			else if (!interFace.compare("ShaderIf"))
			{
				std::shared_ptr<Shader::ShaderIf> shader((Shader::ShaderIf*)constructObject(nameSpace + *it0, *it1));
				storeInContainer(interFace, shader);
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
			FACTORY.getErrorObject()->setError("ERROR: " + objNameIf + " can not be found!");
			FACTORY.getLog()->LOGFILE(LOG "ERROR: " + objNameIf + " can not be found!");
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


	/*! @brief Store object in container
	 *  @param - objNameIf
	 *  @param - derivedObject
	 *  @return void
	 */
	template<class T>
	void storeInContainer(const std::string& objNameIf, const T& derivedObject)
	{
		if (!objNameIf.compare("CameraIf"))
		{
		    m_vecOfCameraIf.push_back(std::dynamic_pointer_cast<Camera::CameraIf>(derivedObject));
		}
		else if (!objNameIf.compare("LoaderIf"))
		{
			m_vecOfLoaderIf.push_back(std::dynamic_pointer_cast<Loader::LoaderIf>(derivedObject));
		}
		else if (!objNameIf.compare("GPUObjectIf"))
		{
			m_vecOfGPUObjectIf.push_back(std::dynamic_pointer_cast<GPUObject::GPUObjectIf>(derivedObject));
		}
		else if (!objNameIf.compare("ModelIf"))
		{
			m_vecOfModelIf.push_back(std::dynamic_pointer_cast<Model::ModelIf>(derivedObject));
		}
		else if (!objNameIf.compare("MeshIf"))
		{
			m_vecOfMeshIf.push_back(std::dynamic_pointer_cast<Mesh::MeshIf>(derivedObject));
		}
		else if (!objNameIf.compare("ShaderIf"))
		{
			m_vecOfShaderIf.push_back(std::dynamic_pointer_cast<Shader::ShaderIf>(derivedObject));
		}
		else
		{
			FACTORY.getErrorObject()->setError("ERROR: " + objNameIf + " can not be found!");
			FACTORY.getLog()->LOGFILE(LOG "ERROR: " + objNameIf + " can not be found!");
		}
	}


	// GET object - TODO: Make this generic
	/*! @brief get object (within particaulary interface) from container
	 *  @param - objNameIf
	 *  @param - derivedObject
	 *  @return void
	 */
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

		FACTORY.getErrorObject()->setError("ERROR: " + arg1 + " can not be found!");
		FACTORY.getLog()->LOGFILE(LOG "ERROR: " + arg1 + " can not be found!");

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

	// DataBase
	std::unique_ptr<Common::Database> m_database;
	// Error
	std::unique_ptr<Common::Error> m_error;
	// Log
	std::unique_ptr<Common::Log> m_log;


	// Container Stuff 
	std::vector<std::shared_ptr<Camera::CameraIf>>       m_vecOfCameraIf;

	std::vector<std::shared_ptr<Loader::LoaderIf>>       m_vecOfLoaderIf;
	std::vector<std::shared_ptr<GPUObject::GPUObjectIf>> m_vecOfGPUObjectIf;

	std::vector<std::shared_ptr<Model::ModelIf>>         m_vecOfModelIf;
	std::vector<std::shared_ptr<Mesh::MeshIf>>           m_vecOfMeshIf;
	std::vector<std::shared_ptr<Shader::ShaderIf>>       m_vecOfShaderIf;
};
} // End of namespace