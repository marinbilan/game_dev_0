#pragma once
#include "shaderIf.h"

#include "error.h"


namespace Shader
{
class TerrainShader : public ShaderIf
{
	const char* vertexShader =
		"	#version 330 \r\n"
		""
		"	in vec3 position;"
		"	in vec2 textureCoords;"
		"	in vec3 normal;"
		""
		"	uniform mat4 projectionMatrix;"
		"	uniform mat4 viewMatrix;"
		"	uniform mat4 viewMatrixInv;"
		"	uniform mat4 transformationMatrix;"
		""
		"	uniform vec3 lightPosition;"
		""
		"	out vec2 pass_textureCoords;"
		"	out vec3 surfaceNormal;"
		"	out vec3 toLightVector;"
		"	out vec3 toCameraVector;"
		""
		"	void main()"
		"	{"
		"		gl_Position =  projectionMatrix * viewMatrix * transformationMatrix * vec4(position, 1.0);"
		"		pass_textureCoords = textureCoords;"
		"		vec4 worldPosition = transformationMatrix * vec4(position, 1.0);"
		"		surfaceNormal = (transformationMatrix * vec4(normal, 0.0)).xyz;"
		"		toLightVector = lightPosition - worldPosition.xyz;"
		"		toCameraVector =  (viewMatrixInv * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;"
		"}";

	const char* fragmentShader =
		"#version 330 \r\n"
		""
		"	in vec2 pass_textureCoords;"
		"	in vec3 surfaceNormal;"
		"	in vec3 toLightVector;"
		"	in vec3 toCameraVector;"
		""
		"	uniform sampler2D backgroundTexture;"
		"	uniform sampler2D rTexture;"
		"	uniform sampler2D gTexture;"
		"	uniform sampler2D bTexture;"
		"	uniform sampler2D blendMap;"
		""
		"	uniform vec3 lightColor;"
		"	uniform float shineDamper;"
		"	uniform float reflectivity;"
		""
		"	out vec4 out_Color;"
		""
		"	void main()"
		"	{"
		"		vec4 blendMapColor = texture(blendMap, pass_textureCoords);"
		"		float backTextureAmount = 1 - (blendMapColor.r + blendMapColor.g + blendMapColor.b);"
		"		vec2 tiledCoords = pass_textureCoords * 40.0;"
		"		vec4 backgroundTextureColor = texture(backgroundTexture, tiledCoords) * backTextureAmount;"
		"		vec4 rTextureColor = texture(rTexture, tiledCoords) * blendMapColor.r;"
		"		vec4 gTextureColor = texture(gTexture, tiledCoords) * blendMapColor.g;"
		"		vec4 bTextureColor = texture(bTexture, tiledCoords) * blendMapColor.b;"
		"		vec4 totalColor = backgroundTextureColor + rTextureColor + gTextureColor + bTextureColor;"
		""
		"		vec3 unitNormal = normalize(surfaceNormal);"
		"		vec3 unitLightVector = normalize(toLightVector);"
		"		float nDot1 = dot(unitNormal, unitLightVector);"
		"		float brightness = max(nDot1, 0.1);"
		"		vec3 diffuse = brightness * lightColor;"
		"		vec3 unitVectorToCamera = normalize(toCameraVector);"
		"		vec3 lightDirection = - unitLightVector;"
		"		vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);"
		"		float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);"
		"		specularFactor = max(specularFactor, 0.0);"
		"		float dampedFactor = pow(specularFactor, shineDamper);"
		"		vec3 finalSpecular = dampedFactor * reflectivity * lightColor;"
		// out_Color = vec4(diffuse, 1.0) * texture(textureSampler, pass_textureCoords) + vec4(finalSpecular, 1.0);
		"		out_Color = vec4(diffuse, 1.0) * totalColor + vec4(finalSpecular, 1.0);"
		"	}";

public:
	TerrainShader(const std::string& name);
	~TerrainShader();

	// FUNCTIONs
	void preInit();
	void postInit();

	const std::string& getName()
	{
		return m_name;
	}


	void render(const glm::mat4& modelMatrix,
		const GPUObject::MeshStructure modelMesh,
		const GPUObject::TextureStructure textureStruct,
		const std::shared_ptr<Camera::CameraIf>& camera,
		const std::shared_ptr<Light::LightIf>& light);

	void render(GLuint VAO, std::shared_ptr<Camera::CameraIf>& m_cameraIf, glm::mat4& m_modelMatrix, const GPUObject::TextureStructure textureStruct, GLuint numInd);

	// OPERATORs
	void printINFO();

	void cmdPrompt(const std::string& arg0);

// Members
//private:
std::string m_name;

GLuint m_shaderProgramID;
glm::mat4 m_projectionMatrix;

// VERTEX SHADER
GLuint m_positionsID;
GLuint m_textureCoordsID;
GLuint m_normalsID;

GLuint m_projectionMatrixID;
GLuint m_viewMatrixID;
GLuint m_viewMatrixInvID;
GLuint m_modelMatrixID;

GLuint m_lightPositionID;

// FRAGMENT SHADER
GLuint m_backgroundTextureID;
GLuint m_rTextureID;
GLuint m_gTextureID;
GLuint m_bTextureID;
GLuint m_blendMapID;

GLuint m_lightColorID;
GLuint m_shineDamperID;
GLuint m_reflectivityID;
};
} // End of namespace