#pragma once

#include "error.h"
#include "modelIf.h"
#include "commonIf.h"

namespace Model
{
class ErrorModel : public ModelIf, public Common::CommonIf
{
public:
	ErrorModel(Common::Error& err, const std::string& name) {};

	~ErrorModel() {};

	// ModelIf
	void preInit() {};
	void postInit() {};

	// ModelIf and CommonIf
	const std::string& getName() 
	{ 
		return m_name; 
	}

	// Impl of CommonIf
	void cmdPrompt(const std::string& arg0) 
	{
		std::cout << "ERROR: ErrorModel called!" << std::endl;
	};

private:
	std::string m_name;
};
}