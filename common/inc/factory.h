#pragma once
#include <map>  
#include <string>  
#include <iostream>  
#include <memory>  
#include <vector>  

#include "error.h"

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
	// ---- xx END xx ----


	// ---- [0] ---- 
	void showMeSeededClasses();

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


	// SET
	// ---- [2] ---- 
	template<class T>
	// args 1] objectName    2] object 
	void storeInContainer(const std::string& objNameIf, T& derivedObject)
	{
		// LoaderIf
		if (!objNameIf.compare("LoaderIf"))
		{
			m_vecOfLoaderIf.push_back(std::dynamic_pointer_cast<Loader::LoaderIf>(derivedObject));
		}
		// GPUObjectIf
		else if (!objNameIf.compare("GPUObjectIf"))
		{
			std::cout << " xxx Stroing in container xxx " << "\n";
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


	// GET - Make this Generic
	// ---- [3] ---- 
	// ADD INTERFACE 
	// LoaderIf
	std::shared_ptr<Loader::LoaderIf>& getLoaderIf(const std::string& arg0);
	// GPUObjectIf
	std::shared_ptr<GPUObject::GPUObjectIf>& getGPUObjectIf(const std::string& arg0);
	// ModelIf
	std::shared_ptr<Model::ModelIf>& getModelIf(const std::string& arg0);	
	// MeshIf
	std::shared_ptr<Mesh::MeshIf>& getMeshIf(const std::string& arg0);
	// ShaderIf
	std::shared_ptr<Shader::ShaderIf>& getShaderIf(const std::string& arg0);


	// Generic getter 
	template<class T>
	auto getObjectFromVec(T& vec0, const std::string& arg1) -> decltype(vec0.at(0))
	{
		for (auto it = vec0.begin(); it != vec0.end(); ++it)
		{
			if (!(*it)->getName().compare(arg1))
			{
				std::cout << "- FOUND -" << (*it)->getName() << " number of shared objects " << (*it).use_count() << std::endl;
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

	// Factory Stuff 
	typedef void*(*constructor_t)(Error&, const std::string&);
	typedef std::map<std::string, constructor_t> mapType;
	mapType m_classesMap;

	//
	// Container Stuff 
	//
	std::vector<std::shared_ptr<Loader::LoaderIf>>       m_vecOfLoaderIf;
	std::vector<std::shared_ptr<GPUObject::GPUObjectIf>> m_vecOfGPUObjectIf;

	std::vector<std::shared_ptr<Model::ModelIf>>         m_vecOfModelIf;
	std::vector<std::shared_ptr<Mesh::MeshIf>>           m_vecOfMeshIf;
	std::vector<std::shared_ptr<Shader::ShaderIf>>       m_vecOfShaderIf;
};
}
 