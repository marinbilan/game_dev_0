#pragma once
#include "modelIf.h"


namespace Model
{
class TerrainModel : public ModelIf
{
public:
	TerrainModel(const std::string& name);
	TerrainModel(const std::string& dbPath, const std::string& name);

	~TerrainModel();

	const std::string& getName() 
	{ 
		return m_name; 
	}

	// ModelIf
	void preInit();
	void postInit();

	// ========================================================================================
    // NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION    NEW OBJECT CREATION
    // ========================================================================================
	void preInitialization();
	void postInitialization();

	// TODO: remove
	GLuint loadTexturePNG(const char* filename);

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

std::shared_ptr<Shader::ShaderIf> m_terrainShaderIf;
std::shared_ptr<GPUObject::GPUObjectIf> m_gpuObjectTextureIf;

GLuint numInd;

// OpenGL
GLuint vboID1;
GLuint vboID2;
GLuint vboID3;
GLuint indexBufferID;

GLuint backgroundTextureID;
GLuint rTextureID;
GLuint gTextureID;
GLuint bTextureID;
GLuint blendMapID;
};
} // end of namespace