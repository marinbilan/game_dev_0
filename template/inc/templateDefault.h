#pragma once

#include "templateIf.h"
#include "error.h"

namespace Template
{
class TemplateDefault : public TemplateIf
{
public:
	TemplateDefault(Common::Error& err, const std::string& name);

	~TemplateDefault();

	void preInit();

	void postInit();

private:
	std::string m_name;
};
}