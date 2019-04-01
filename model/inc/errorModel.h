#pragma once

#include "error.h"
#include "modelIf.h"


namespace Model
{
class ErrorModel : public ModelIf
{
public:
	ErrorModel(Common::Error& err, const std::string& name) {};

	~ErrorModel() {};

    void render() {};

	// ModelIf
	void preInit() {};
	void postInit() {};

	const std::string& getName() 
	{ 
		return m_name; 
	}

	void cmdPrompt(const std::string& arg0) 
	{
		std::cout << "ERROR: ErrorModel cmdPrompt called!" << std::endl;
	};

private:
std::string m_name;
};
}