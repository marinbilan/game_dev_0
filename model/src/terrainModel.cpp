#include "terrainModel.h"

#include "factory.h"


Model::TerrainModel::TerrainModel(const std::string& dbPath, const std::string& name) :
	m_dbPath(dbPath),
	m_name(name),
	m_modelPosition(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_modelScale(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_modelRotateAround(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_angle(0.0f),
	m_modelMatrix(glm::mat4(0.0f))
{
	m_dbPathWithName = m_dbPath + m_name + "_";

	std::string instName = m_dbPathWithName + m_name;
	FACTORY.getLog()->LOGFILE(LOG "TerrainModel: " + m_name + " created.");
}


Model::TerrainModel::~TerrainModel()
{
}


void Model::TerrainModel::preInitialization()
{
	FACTORY.getLog()->LOGFILE(LOG "TerrainModel " + m_name + " preInit method called!");

	// Create Terrain
	createTerrainAndVAO();

	// 1] Update model position
	std::string dBKey = m_dbPathWithName + "position";

	FACTORY.getDatabase()->getVec3(dBKey, m_modelPosition);
	m_modelMatrix = glm::translate(glm::mat4(1.0f), m_modelPosition);

	// 2] Update model rotation around axes
	dBKey = m_dbPathWithName + "angle";
	FACTORY.getDatabase()->getFloat(dBKey, m_angle);

	dBKey = m_dbPathWithName + "rotateAround";
	FACTORY.getDatabase()->getVec3(dBKey, m_modelRotateAround);

	// 3] Update model with scale factor
	dBKey = m_dbPathWithName + "modelScale";
	FACTORY.getDatabase()->getVec3(dBKey, m_modelScale);

	// MODEL VARIABLES
	m_modelMatrix = glm::mat4(1.0f);
	m_modelMatrix = glm::translate(glm::mat4(1.0f), m_modelPosition);
	m_modelMatrix = glm::rotate(m_modelMatrix, m_angle, m_modelRotateAround);
	m_modelMatrix = glm::scale(m_modelMatrix, m_modelScale);
}


void Model::TerrainModel::postInitialization()
{
	// 1] Get Camera
	std::string dBKey = m_dbPathWithName + "camera";
	std::vector<std::string> cameraString;
	FACTORY.getDatabase()->getStringsFromDB(dBKey, cameraString);
	m_cameraIf = Common::Factory::getInstance().getCameraIf(cameraString[0]);

	// 2] Get Light
	dBKey = m_dbPathWithName + "light";
	std::vector<std::string> lightString;
	FACTORY.getDatabase()->getStringsFromDB(dBKey, lightString);
	m_lightIf = Common::Factory::getInstance().getLightIf(lightString[0]);

	// 3] Get TextureObject
	dBKey = m_dbPathWithName + "textureObjectModel";
	std::vector<std::string> textureTerrainModelString;
	FACTORY.getDatabase()->getStringsFromDB(dBKey, textureTerrainModelString);

	m_gpuObjectTextureIf = Common::Factory::getInstance().getGPUObjectIf(textureTerrainModelString[0]);

	// 4] Get Shader(s)
	dBKey = m_dbPathWithName + "shaders";
	std::vector<std::string> shadersString;
	FACTORY.getDatabase()->getStringsFromDB(dBKey, shadersString);
	m_terrainShaderIf = FACTORY.getShaderIf(shadersString[0]);
}


void Model::TerrainModel::createTerrainAndVAO()
{
	// LOAD TERRAIN
	// -------------
	GLfloat SIZE = 800;
	GLuint VERTEX_COUNT = 128;

	GLuint count = VERTEX_COUNT * VERTEX_COUNT;

	GLfloat* vertices;
	GLfloat* normals;
	GLfloat* textureCoords;
	GLuint* indices;

	vertices = new GLfloat[count * 3];
	textureCoords = new GLfloat[count * 2];
	normals = new GLfloat[count * 3];
	indices = new GLuint[6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1)];

	numInd = 6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1);

	GLuint vertexPointer = 0;

	for (int i = 0; i < VERTEX_COUNT; i++) {
		for (int j = 0; j < VERTEX_COUNT; j++) {

			vertices[vertexPointer * 3] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
			vertices[vertexPointer * 3 + 1] = 0; // H[i][j]; // getHeight(120, 20, &fif, dib); //  40 * sin(0.1*i) + 40 * sin(0.1*j);
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;

			textureCoords[vertexPointer * 2] = (float)j / ((float)VERTEX_COUNT - 1);
			textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)VERTEX_COUNT - 1);

			normals[vertexPointer * 3] = 0;
			normals[vertexPointer * 3 + 1] = 1;
			normals[vertexPointer * 3 + 2] = 0;

			vertexPointer++;
		}
	}

	GLuint pointer = 0;

	for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {

			int topLeft = (gz * VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;

			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}
	// ----

	// ----
	// CREATE VAO 
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// CREATE VBOs
	glGenBuffers(1, &m_vboID1);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID1);
	glBufferData(GL_ARRAY_BUFFER, 3 * count * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &m_vboID2);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID2);
	glBufferData(GL_ARRAY_BUFFER, 2 * count * sizeof(GLfloat), textureCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &m_vboID3);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID3);
	glBufferData(GL_ARRAY_BUFFER, 3 * count * sizeof(GLfloat), normals, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &m_indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numInd * sizeof(GLuint), indices, GL_STATIC_DRAW);
	// ----
}


void Model::TerrainModel::render()
{
	m_terrainShaderIf->render(m_VAO, m_cameraIf, m_lightIf, m_modelMatrix, m_gpuObjectTextureIf->getTextureStructVec()[0], numInd);
};


void Model::TerrainModel::cmdPrompt(const std::string& arg0)
{
	
}
