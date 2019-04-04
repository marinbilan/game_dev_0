#pragma once

#include "controlIf.h"
#include "error.h"

namespace Control
{
class ControlDefault : public ControlIf
{
public:
	ControlDefault(Common::Error& err, const std::string& name);

	~ControlDefault();

	void preInit();

	void postInit();

private:
	std::string m_name;
};
}