#pragma once
#include "meshIf.h"

#include "error.h"


namespace Mesh
{
class ErrorMesh : public MeshIf
{
public:
	ErrorMesh(Common::Error& err, const std::string& name) {};

	~ErrorMesh() {};

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
		std::cout << "ERROR: ErrorMesh called!" << std::endl;
	};

private:
std::string m_name;
};
}