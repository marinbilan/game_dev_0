#pragma once
#include <iostream>
#include <vector>

#include "glew.h"


namespace GPUObject
{
class GPUObjectIf
{
public:
	~GPUObjectIf()
	{
		std::cout << "GPUObjectIf destructor called!" << '\n';
	}

	virtual const std::string& getName()
	{
		return "not implemented in LoaderIf";
	}

	virtual void preInit() {};
	virtual void postInit() {};

	// modelGPUObjectIf
	virtual void setVAO(GLuint VAO)
	{
		std::cout << " ERROR: setVAO called from GUPObjectIf" << '\n';
	}

	virtual GLuint getVAO()
	{
		std::cout << " ERROR: getVAO called from GUPObjectIf" << '\n';
		return 0;
	}

	virtual void setVBO(GLuint VBO)
	{
		std::cout << " ERROR: setVBO called from GUPObjectIf" << '\n';
	}

	virtual void setIBO(GLuint IBO)
	{
		std::cout << " ERROR: setIBO called from GUPObjectIf" << '\n';
	}

	virtual void setNumOfInd(GLuint numOfInd)
	{
		std::cout << " ERROR: setNumOfInd called from GUPObjectIf" << '\n';
	}

	// GET std::vector<GLuint> m_vecOfVBOs
	virtual std::vector<GLuint>& getVecOfVBOs()
	{
		std::cout << " ERROR: getVecOfVBOs called from GUPObjectIf" << '\n';

		std::vector<GLuint> temp {0};
		return temp;
	}

	virtual std::vector<GLuint>& getVecOfIBOs()
	{
		std::cout << " ERROR: getVecOfVBOs called from GUPObjectIf" << '\n';

		std::vector<GLuint> temp{ 0 };
		return temp;
	}

	virtual std::vector<GLuint>& getVecOfNumOfInds()
	{
		std::cout << " ERROR: getVecOfVBOs called from GUPObjectIf" << '\n';

		std::vector<GLuint> temp{ 0 };
		return temp;
	}

	// TEXTURE STUFF
	virtual void setTextureID(GLuint textureID) {}
	virtual GLuint getTextureID() { return 0; }

	virtual void info() {}
};
}