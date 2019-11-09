#pragma once
#include "modelIf.h"


namespace Model
{
class StaticModel : public ModelIf
{
public:
	StaticModel(const std::string& name);
	StaticModel(const std::string& dbPath, const std::string& name);

	~StaticModel();

	const std::string& getName() 
	{ 
		return m_name; 
	}

	void preInitialization();
	void postInitialization();

    void render();

	void dump();

	void cmdPrompt(const std::string& arg0);

private:
std::string m_dbPath;
std::string m_dbPathWithName;
std::string m_name;
GLuint      m_VAO;

// PreInitialization
glm::vec3  m_modelPosition;
glm::vec3  m_modelScale;
glm::vec3  m_modelRotateAround;
GLfloat    m_angle;

glm::mat4  m_modelMatrix;

// PostInitialization
std::shared_ptr<Camera::CameraIf> m_cameraIf;
std::shared_ptr<Light::LightIf>   m_lightIf;

std::shared_ptr<GPUObject::GPUObjectIf>        m_gpuObjectIf;
std::shared_ptr<GPUObject::GPUObjectIf>        m_gpuObjectTextureIf;
std::vector<std::shared_ptr<Shader::ShaderIf>> m_vecOfdefaultShaderIf;
};
} // end of namespace