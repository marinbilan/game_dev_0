#pragma once

#include "error.h"
#include "modelIf.h"
#include "commonIf.h"

namespace Model
{
class StaticModel : public ModelIf, public Common::CommonIf
{
public:
	StaticModel(Common::Error& err, const std::string& name);

	~StaticModel();

	// ModelIf
	void preInit();
	void postInit();

	// ModelIf and CommonIf
	const std::string& getName() 
	{ 
		return m_name; 
	}

	// Impl of ModelIf
	void cmdPrompt(const std::string& arg0);

private:
	std::string m_name;
};
}