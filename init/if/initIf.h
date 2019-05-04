#pragma once
#include <iostream>
#include <string>


namespace Init
{
class InitIf
{
public:
	~InitIf()
	{
		std::cout << "Error: InitIf::~InitIf() called from InitIf!" << '\n';
	}

	// TODO: getName

	virtual void preInit() {};
	virtual void postInit() {};

	// Register all new derived classes
	virtual void registerClass() {};

	virtual void createCameras() {};

	virtual void createLoaders() {};

	virtual void createModels() {};
	virtual void createMeshes() {};
	virtual void createShaders() {};
};
}