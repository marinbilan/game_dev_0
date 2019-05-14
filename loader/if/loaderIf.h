#pragma once
#include <iostream>
#include <vector>
#include <memory>

// OpenGL
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
	~LoaderIf()
	{
		std::cout << "LoaderIf destructor called!" << '\n';
	}
	//
	// Common
	//
	virtual const std::string& getName()
	{
		return "not implemented in LoaderIf";
	}

	virtual void preInit() {};
	virtual void postInit() {};

	// ModelLoader

	// TextureLoader
	virtual GLuint createTexture(const std::string& _textureName) { return 0; };
};
}