#pragma once
#include <map>  
#include <string>  
#include <iostream>  
#include <memory>  
#include <vector>  

#include "error.h"
#include "commonIf.h"

#include "modelIf.h"
#include "staticModel.h"
#include "errorModel.h"
#include "meshIf.h"
#include "defaultMesh.h"


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
	// Singleton stuff
	static Factory& getInstance()
	{
		static Factory instance;
		return instance;
	}

	Factory(Factory const&) = delete;
	void operator=(Factory const&) = delete;

	~Factory() {};
	//


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


	// Methods 
	void showMeSeededClasses()
	{
		mapType::iterator it;
		for (it = m_classesMap.begin(); it != m_classesMap.end(); ++it)
		{
			std::cout << " - " << it->first << std::endl;
		}
	}

	void showMeCommonIfObjects()
	{
		for (auto it = m_vecOfCommonIf.begin(); it != m_vecOfCommonIf.end(); ++it)
		{
			std::cout << " commonIf object: " << (*it)->getName() << std::endl;

		}
	}

	void showMeModelIfObjects()
	{
		for (auto it = m_vecOfModelIf.begin(); it != m_vecOfModelIf.end(); ++it)
		{
			std::cout << " commonIf object: " << (*it)->getName() << std::endl;

		}
	}

	// Container Stuff
	// STORE
	void storeInContainer(std::shared_ptr<Model::StaticModel>& arg0)
	{
		m_vecOfModelIf.push_back(std::dynamic_pointer_cast<Model::ModelIf>(arg0));
		m_vecOfCommonIf.push_back(std::dynamic_pointer_cast<CommonIf>(arg0));
	}


	void storeInContainer(std::shared_ptr<Mesh::DefaultMesh>& arg0)
	{
			m_vecOfMeshIf.push_back(std::dynamic_pointer_cast<Mesh::MeshIf>(arg0));
			m_vecOfCommonIf.push_back(std::dynamic_pointer_cast<CommonIf>(arg0));
	}


	// GET
	std::shared_ptr<CommonIf>& getCommonIf(Error& err, const std::string& arg0)
	{
		for (auto it = m_vecOfCommonIf.begin(); it != m_vecOfCommonIf.end(); ++it)
		{
			if (!(*it)->getName().compare(arg0))
			{
				std::cout << "- FOUND -" << (*it)->getName() << " number of shared objects " << (*it).use_count() << std::endl;
				return *it;
			}

		}

	}

	std::shared_ptr<Model::ModelIf>& getModelIf(const std::string& arg0)
	{
		for (auto it = m_vecOfModelIf.begin(); it != m_vecOfModelIf.end(); ++it)
		{
			if (!(*it)->getName().compare(arg0))
			{
				std::cout << "- FOUND -" << (*it)->getName() << " number of shared objects " << (*it).use_count() << std::endl;
				return *it;
			}
		}

		Error err;
		err.setError("ERROR: Unbale to find object! Returning default!");
		err.printError();

		return errorModel;
	}

	
	std::shared_ptr<Mesh::MeshIf>& getMeshIf(const std::string& arg0)
	{
		for (auto it = m_vecOfMeshIf.begin(); it != m_vecOfMeshIf.end(); ++it)
		{
			if (!(*it)->getName().compare(arg0))
			{
				std::cout << "- FOUND -" << (*it)->getName() << " number of shared objects " << (*it).use_count() << std::endl;
				return *it;
			}

		}
	}

private:
	
	// Singleton Factory - Constructor private
	Factory() 
	{
		Error err;
		errorModel = std::make_shared<Model::ErrorModel>(err, "errorModel");
	};

	// Factory Stuff 
	typedef void*(*constructor_t)(Error&, const std::string&);
	typedef std::map<std::string, constructor_t> mapType;
	mapType m_classesMap;

	// Container Stuff  
	std::vector<std::shared_ptr<CommonIf>> m_vecOfCommonIf;

	std::vector<std::shared_ptr<Model::ModelIf>> m_vecOfModelIf;
	std::vector<std::shared_ptr<Mesh::MeshIf>> m_vecOfMeshIf;

	// Error Objects
	std::shared_ptr<Model::ModelIf> errorModel;
};

}
 