#pragma once
#include "gpuObjectIf.h"

#include <vector>

#include "error.h"


namespace GPUObject
{
class ModelGPUObject : public GPUObjectIf
{
public:
	ModelGPUObject(Common::Error& err, const std::string& name);

	~ModelGPUObject();
	
	const std::string& getName();

	void preInit();
	void postInit();

	// modelGPUObjectIf
	void setVAO(GLuint VAO);
	GLuint getVAO();

	void setVBO(GLuint VBO);

	void setIBO(GLuint IBO);

	void setNumOfInd(GLuint numOfInd);

	// GET
	virtual std::vector<GLuint>& getVecOfVBOs();
	virtual std::vector<GLuint>& getVecOfIBOs();
	virtual std::vector<GLuint>& getVecOfNumOfInds();

	void info();

// private:
	std::string m_name;

	GLuint m_VAO;
	std::vector<GLuint> m_vecOfVBOs;
	std::vector<GLuint> m_vecOfIBOs;
	std::vector<GLuint> m_vecOfNumOfInds;
};
}