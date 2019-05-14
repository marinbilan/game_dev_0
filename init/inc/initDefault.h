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

	void registerClass();

private:
	void createObjects(const std::string& name_space, const std::string& inter_face);

// Members
std::string m_name;
};
}