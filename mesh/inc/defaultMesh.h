#pragma once

#include "error.h"
#include "meshIf.h"
#include "commonIf.h"

namespace Mesh
{
class DefaultMesh : public MeshIf, public Common::CommonIf
{
public:
	DefaultMesh(Common::Error& err, const std::string& name);

	~DefaultMesh();

	// ModelIf
	void preInit();
	void postInit();

	// ModelIf and CommonIf
	const std::string& getName() 
	{ 
		return m_name; 
	}

private:
	std::string m_name;
};
}