#pragma once
#include "shaderIf.h"

#include "error.h"


namespace Shader
{
class NormalMapShader : public ShaderIf
{
	const char* VertexShaderNormalMapPTNT =
		"#version 330 \r\n"
		""
		"    in vec3 position;"
		"    in vec2 textureCoordinates;"
		"    in vec3 normal;"
		"    in vec3 tangent;"
		""
		"    uniform mat4 projectionMatrix;"
		"    uniform mat4 viewMatrix;"
		"    uniform mat4 transformationMatrix;"
		""
		"    uniform vec3 lightPositionEyeSpace;" // MULTIPLE
		""
		"    const float density = 0;"
		"    const float gradient = 5.001;"
		""
		"    out vec2 pass_textureCoordinates;"
		"    out vec3 toLightVector;" // MULTIPLE
		"    out vec3 toCameraVector;"
		"    out float visibility;"
		""
		"   void main(void) {"
		""
		"	   vec4 worldPosition = transformationMatrix * vec4(position, 1.0);"
		"	   mat4 modelViewMatrix = viewMatrix * transformationMatrix;"
		"	   vec4 positionRelativeToCam = modelViewMatrix * vec4(position, 1.0);"
		"	   gl_Position = projectionMatrix * positionRelativeToCam;"
		""
		"	   pass_textureCoordinates = textureCoordinates;"
		""
		"	   vec3 surfaceNormal = (modelViewMatrix * vec4(normal, 0.0)).xyz;"
		""
		"	vec3 norm = normalize(surfaceNormal);"
		"	vec3 tang = normalize((modelViewMatrix * vec4(tangent, 0.0)).xyz);"
		"	vec3 bitang = normalize(cross(norm, tang));"
		""
		"	mat3 toTangentSpace = mat3("
		"		tang.x, bitang.x, norm.x,"
		"		tang.y, bitang.y, norm.y,"
		"		tang.z, bitang.z, norm.z"
		"		);"
		""
		"	toLightVector = toTangentSpace * ( (viewMatrix * vec4(lightPositionEyeSpace, 1.0)).xyz - positionRelativeToCam.xyz);"
		"	toCameraVector = toTangentSpace * (-positionRelativeToCam.xyz);"
		""
		"	float distance = length(positionRelativeToCam.xyz);"
		"	visibility = exp(-pow((distance*density), gradient));"
		"	visibility = clamp(visibility, 0.0, 1.0);"
		""
		"}";
	const char* FragmentShaderNormalMapPTNT =
		"#version 330 \r\n"
		""
		"   in vec2 pass_textureCoordinates;"
		"   in vec3 toLightVector;" // MULTIPLE
		"   in vec3 toCameraVector;"
		"   in float visibility;"
		""
		"   uniform vec3 lightColour;" // MULTIPLE
		"   uniform float shineDamper;"
		"   uniform float reflectivity;"
		""
		"   uniform sampler2D modelTexture;"
		"   uniform sampler2D normalMap;"
		""
		"   out vec4 out_Color;"
		""
		"   void main(void) {"
		""
		"	   vec4 normalMapValue = 2.0 * texture(normalMap, pass_textureCoordinates, -1.0) - 1.0;"
		""
		"	   vec3 unitNormal = normalize(normalMapValue.rgb);"
		"	   vec3 unitVectorToCamera = normalize(toCameraVector);"
		""
		"	   vec3 totalDiffuse = vec3(0.0);"
		"	   vec3 totalSpecular = vec3(0.0);"
		""
		"		float distance = length(toLightVector);"
		"		vec3 attenuation = vec3(0.001);"
		"		float attFactor = attenuation.x + (attenuation.y * distance) + (attenuation.z * distance * distance);"
		"		vec3 unitLightVector = normalize(toLightVector);"
		"		float nDotl = dot(unitNormal, unitLightVector);"
		"		float brightness = max(nDotl, 0.0);"
		"		vec3 lightDirection = -unitLightVector;"
		"		vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);"
		"		float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);"
		"		specularFactor = max(specularFactor, 0.0);"
		"		float dampedFactor = pow(specularFactor, shineDamper);"
		"		totalDiffuse = totalDiffuse + (brightness * lightColour) / attFactor;"
		"		totalSpecular = totalSpecular + (dampedFactor * reflectivity * lightColour) / attFactor;"
		""
		"   totalDiffuse = max(totalDiffuse, 0.1);"
		""
		"   vec4 textureColour = texture(modelTexture, pass_textureCoordinates, -1.0);"
		"   if (textureColour.a<0.5) {"
		"		discard;"
		"	}"
		""
		"   out_Color = vec4(totalDiffuse, 1.0) * textureColour + vec4(totalSpecular, 1.0);"
		//"	out_Color = mix(vec4(skyColour, 1.0), out_Color, visibility);"
		""
		"}";

public:
	NormalMapShader(const std::string& dbPath, const std::string& name);
	~NormalMapShader();

	void preInitialization();
	void postInitialization();

	const std::string& getName()
	{
		return m_name;
	}

	void render(const glm::mat4& modelMatrix,
		const GPUObject::MeshStructure modelMesh,
		const GPUObject::TextureStructure textureStruct,
		const std::shared_ptr<Camera::CameraIf>& camera,
		const std::shared_ptr<Light::LightIf>& light);


	// OPERATORs
	void printINFO();

	friend std::ostream& operator<<(std::ostream& output, NormalMapShader& info)
	{
		output << "" << std::endl;
		output << "[ SHADER ]" << std::endl;
		output << " Shader Name:              " << info.m_name << std::endl;
		output << " ShaderProgramID:          " << info.m_shaderProgramID << std::endl;
		output << "  [ VERTEX SHADER ]" << std::endl;
		output << "     positionsID         = " << info.m_positionsID << std::endl;
		output << "     textureCoordsID     = " << info.m_textureCoordsID << std::endl;
		output << "     normalsID           = " << info.m_normalsID << std::endl;
		output << "     tangentsID          = " << info.m_tangentsID << std::endl;
		output << "      projectionMatrixID = " << info.m_projectionMatrixID << std::endl;
		output << "      viewMatrixID       = " << info.m_viewMatrixID << std::endl;
		output << "      modelMatrixID      = " << info.m_modelMatrixID << std::endl;
		output << "      lightPosEyeSpID    = " << info.m_lightPositionEyeSpaceID << std::endl;
		output << "  [ FRAGMENT SHADER ]" << std::endl;
		output << "      lightColourID      = " << info.m_lightColourID << std::endl;
		output << "      shineDamperID      = " << info.m_shineDamperID << std::endl;
		output << "      reflectivityID     = " << info.m_reflectivityID << std::endl;
		output << "      modelTextureID     = " << info.m_modelTextureID << std::endl;
		output << "      modelNormalMapID   = " << info.m_modelNormalMapID << std::endl;
		output << "" << std::endl;
		return output;
	}

	void cmdPrompt(const std::string& arg0);

// Members
//private:
std::string m_dbPath;
std::string m_dbPathWithName;
std::string m_name;

glm::mat4   m_projectionMatrix;

GLuint m_shaderProgramID;

// VERTEX SHADER
GLuint m_positionsID;
GLuint m_textureCoordsID;
GLuint m_normalsID;
GLuint m_tangentsID;

GLuint m_projectionMatrixID;
GLuint m_viewMatrixID;
GLuint m_modelMatrixID;
GLuint m_lightPositionEyeSpaceID;

// FRAGMENT SHADER
GLuint m_lightColourID;
GLuint m_shineDamperID;
GLuint m_reflectivityID;

GLuint m_modelTextureID;
GLuint m_modelNormalMapID;
};
}