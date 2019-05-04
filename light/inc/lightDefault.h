#pragma once

#include "lightIf.h"
#include "error.h"

namespace Light
{
class LightDefault : public LightIf
{
public:
	LightDefault(Common::Error& err, const std::string& name);

	~LightDefault();

	void preInit();
	void postInit();

private:
	std::string m_name;
};
}