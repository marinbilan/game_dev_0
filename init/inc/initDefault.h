#pragma once
#include "initIf.h"


namespace Init
{
class InitDefault : public InitIf
{
public:
	InitDefault(const std::string& name);

	~InitDefault();

	void preInit();
	void postInit();

private:

std::string m_name;

};
}