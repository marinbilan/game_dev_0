#pragma once
#include "initIf.h"

#include <iostream>
#include <string>

#include "error.h"


namespace Init
{
class InitDefault : public InitIf
{
public:
	InitDefault(Common::Error& err, const std::string& name);

	~InitDefault();

	void preInit();

	void postInit();

	void registerClass();

	void createModels();

	void createMeshes();

	void createShaders();

private:
std::string m_name;
};
}