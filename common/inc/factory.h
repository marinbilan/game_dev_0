#pragma once
#include <map>  
#include <string>  
#include <iostream>  
#include <memory>  
#include <vector>  

#include "error.h"
#include "commonIf.h"


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

	// Container Stuff 
	// SET
	/*
	void storeInContainer(std::shared_ptr<DefaultMesh>& arg0)
	{
			std::cout << typeid(arg0).name() << std::endl;
			m_vecOfDefaultMeshIf.push_back(std::dynamic_pointer_cast<DefaultMeshIf>(arg0));
			m_vecOfCommonIf.push_back(std::dynamic_pointer_cast<CommonIf>(arg0));
	}

	void storeInContainer(std::shared_ptr<DefaultLight>& arg0)
	{
			std::cout << typeid(arg0).name() << std::endl;
			m_vecOfDefaultLightIf.push_back(std::dynamic_pointer_cast<DefaultLightIf>(arg0));
			m_vecOfCommonIf.push_back(std::dynamic_pointer_cast<CommonIf>(arg0));
	}
	*/

	// GET
	std::shared_ptr<CommonIf>& getCommonIf(std::string& arg0)
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
	/*
		std::shared_ptr<DefaultMeshIf>& getDefaultMeshIf(std::string& arg0)
		{
			for (auto it = m_vecOfDefaultMeshIf.begin(); it != m_vecOfDefaultMeshIf.end(); ++it)
			{
				if (!(*it)->getName().compare(arg0))
				{
					std::cout << "- FOUND -" << (*it)->getName() << " number of shared objects " << (*it).use_count() << std::endl;
					return *it;
				}

			}
		}
	*/
	/*
		std::shared_ptr<DefaultLightIf>& getDefaultLightIf(std::string& arg0)
		{
			for (auto it = m_vecOfDefaultLightIf.begin(); it != m_vecOfDefaultLightIf.end(); ++it)
			{
				if (!(*it)->getName().compare(arg0))
				{
					std::cout << "- FOUND -" << (*it)->getName() << " number of shared objects " << (*it).use_count() << std::endl;
					return *it;
				}

			}
		}
	*/

private:
	// Factory Stuff 
	typedef void*(*constructor_t)(Error&, const std::string&);
	typedef std::map<std::string, constructor_t> mapType;
	mapType m_classesMap;

	// Container Stuff  
	std::vector<std::shared_ptr<CommonIf>> m_vecOfCommonIf;

	//	std::vector<std::shared_ptr<DefaultMeshIf>> m_vecOfDefaultMeshIf;
	//	std::vector<std::shared_ptr<DefaultLightIf>> m_vecOfDefaultLightIf;
};

}

Common::Factory defaultFactory;
#define REGISTER_CLASS(ConstructorName) defaultFactory.registerClass<ConstructorName>(#ConstructorName)  