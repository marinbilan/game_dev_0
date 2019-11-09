#pragma once
#include <iostream>
#include <vector>
#include <memory>

#include "error.h"
#include "glew.h"
// Assimp
#include "Importer.hpp"
#include "postprocess.h"
#include "mesh.h"
#include "scene.h"
// GLM
#include "glm.hpp"
// FreeImage
#include "FreeImage.h"


namespace Loader
{
class LoaderIf
{
public:
	~LoaderIf() {}

	virtual const std::string& getName()
	{
		return "not implemented in LoaderIf";
	}

	virtual void preInitialization() {};
	virtual void postInitialization() {};

	// ModelLoader

	// TextureLoader
	virtual GLuint createTexture(const std::string& _textureName) { return 0; };
};
}