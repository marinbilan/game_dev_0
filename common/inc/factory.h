#pragma once
#include <map>  
#include <string>  
#include <iostream>  
#include <memory>  
#include <vector>  

#include "error.h"

#include "modelIf.h"
#include "staticModel.h"
#include "meshIf.h"
#include "defaultMesh.h"
#include "shaderIf.h"
#include "defaultShader.h"

#include "errorModel.h"
#include "errorMesh.h"
#include "errorShader.h"


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
	// ---- ----

	// Methods 
	void showMeSeededClasses();

	void showMeModelIfObjects();

	void showMeMeshIfObjects();

	void showMeShaderIfObjects();

	// Container Stuff
	// STORE
	void storeInContainer(std::shared_ptr<Model::StaticModel>& arg0);

	void storeInContainer(std::shared_ptr<Mesh::DefaultMesh>& arg0);

	void storeInContainer(std::shared_ptr<Shader::DefaultShader>& arg0);

	// GET
	std::shared_ptr<Model::ModelIf>& getModelIf(const std::string& arg0);
	
	std::shared_ptr<Mesh::MeshIf>& getMeshIf(const std::string& arg0);

	std::shared_ptr<Shader::ShaderIf>& getShaderIf(const std::string& arg0);

private:	
	// Singleton Factory - Constructor private
	Factory() 
	{
		Error err;
		errorModel = std::make_shared<Model::ErrorModel>(err, "errorModel");
		errorMesh = std::make_shared<Mesh::ErrorMesh>(err, "errorMesh");
		errorShader = std::make_shared<Shader::ErrorShader>(err, "errorShader");
	};

	// Factory Stuff 
	typedef void*(*constructor_t)(Error&, const std::string&);
	typedef std::map<std::string, constructor_t> mapType;
	mapType m_classesMap;

	// Container Stuff  
	std::vector<std::shared_ptr<Model::ModelIf>> m_vecOfModelIf;
	std::vector<std::shared_ptr<Mesh::MeshIf>> m_vecOfMeshIf;
	std::vector<std::shared_ptr<Shader::ShaderIf>> m_vecOfShaderIf;

	// Error Objects
	std::shared_ptr<Model::ModelIf> errorModel;
	std::shared_ptr<Mesh::MeshIf> errorMesh;
	std::shared_ptr<Shader::ShaderIf> errorShader;
};

}
 