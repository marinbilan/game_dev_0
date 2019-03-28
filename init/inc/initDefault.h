#pragma once
#include <iostream>
#include <string>

#include "initIf.h"
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

	void createDefaultObject();

private:
	std::string m_name;
};
}