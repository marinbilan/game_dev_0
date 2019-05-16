#pragma once
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

private:
std::string m_name;
};
}