#pragma once
#include "modelIf.h"


namespace Model
{
class TerrainModel : public ModelIf
{
public:
	TerrainModel(const std::string& dbPath, const std::string& name);
	~TerrainModel();

	const std::string& getName() 
	{ 
		return m_name; 
	}

	void preInitialization();
	void postInitialization();

	void createTerrainAndVAO();

    void render();

	void cmdPrompt(const std::string& arg0);

private:
std::string m_dbPath;
std::string m_dbPathWithName;
std::string m_name;

GLuint m_VAO;

glm::vec3                 m_modelPosition;
glm::vec3                 m_modelScale;
glm::vec3                 m_modelRotateAround;
GLfloat                   m_angle;

glm::mat4                 m_modelMatrix;

std::shared_ptr<Camera::CameraIf> m_cameraIf;
std::shared_ptr<Light::LightIf>   m_lightIf;

std::shared_ptr<GPUObject::GPUObjectIf> m_gpuObjectTextureIf;
std::shared_ptr<Shader::ShaderIf> m_terrainShaderIf;

GLuint numInd;

// OpenGL stuff
GLuint m_vboID1;
GLuint m_vboID2;
GLuint m_vboID3;
GLuint m_indexBufferID;

};
} // end of namespace