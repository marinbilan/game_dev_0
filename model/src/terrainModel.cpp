#include "terrainModel.h"

#include "factory.h"


Model::TerrainModel::TerrainModel(const std::string& name) :
	m_name(name), 
	m_modelPosition(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_modelScale(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_modelRotateAround(glm::vec3(0.0f, 0.0f, 0.0f)),
    m_angle(0.0f),
	m_modelMatrix(glm::mat4(0.0f))
{
	FACTORY.getLog()->LOGFILE(LOG "StaticModel " + m_name + " created!");
}


Model::TerrainModel::~TerrainModel()
{
}


void Model::TerrainModel::preInit()
{
	FACTORY.getLog()->LOGFILE(LOG "TerrainModel " + m_name + " preInit method called!");

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
	vboID1;
	glGenBuffers(1, &vboID1);
	glBindBuffer(GL_ARRAY_BUFFER, vboID1);
	glBufferData(GL_ARRAY_BUFFER, 3 * count * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	vboID2;
	glGenBuffers(1, &vboID2);
	glBindBuffer(GL_ARRAY_BUFFER, vboID2);
	glBufferData(GL_ARRAY_BUFFER, 2 * count * sizeof(GLfloat), textureCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	vboID3;
	glGenBuffers(1, &vboID3);
	glBindBuffer(GL_ARRAY_BUFFER, vboID3);
	glBufferData(GL_ARRAY_BUFFER, 3 * count * sizeof(GLfloat), normals, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	indexBufferID;
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numInd * sizeof(GLuint), indices, GL_STATIC_DRAW);
	// ----


	// MODEL VARIABLES
	m_modelPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	m_modelRotateAround = glm::vec3(1.0f, 0.0f, 0.0f);
	m_modelScale = glm::vec3(1.0f, 1.0f, 1.0f);

	m_angle = 0.0;

	m_modelMatrix = glm::mat4(1.0f);
	m_modelMatrix = glm::translate(glm::mat4(1.0f), m_modelPosition);
	m_modelMatrix = glm::rotate(m_modelMatrix, m_angle, m_modelRotateAround);
	m_modelMatrix = glm::scale(m_modelMatrix, m_modelScale);


	// TODO: remove from here
	backgroundTextureID = loadTexturePNG("_src/textures/grass.png");
	rTextureID = loadTexturePNG("_src/textures/dirt.png");
	gTextureID = loadTexturePNG("_src/textures/sand.png");
	bTextureID = loadTexturePNG("_src/textures/hardwood.png");
	blendMapID = loadTexturePNG("_src/textures/blendMap2.png");
}


void Model::TerrainModel::postInit()
{
	FACTORY.getLog()->LOGFILE(LOG "TerrainModel " + m_name + " postInit method called!");

	// Get Shader
	std::string shaderName;
	FACTORY.getDatabase()->getStringFromDB(m_name, "shader", shaderName);
	m_terrainShaderIf = FACTORY.getShaderIf(shaderName);

	std::string gpuObjectTextureString;
	FACTORY.getDatabase()->getStringFromDB(m_name, "GPUObjectTexture", gpuObjectTextureString);
	m_gpuObjectTextureIf = Common::Factory::getInstance().getGPUObjectIf(gpuObjectTextureString);

	// Get Camera
	std::string cameraName;
	FACTORY.getDatabase()->getStringFromDB(m_name, "camera", cameraName);
	m_cameraIf = FACTORY.getCameraIf(cameraName);

}

// 1 ] Bind VAO        (glBindVertexArray (VAO)); 
// 2 ] Bind VBO        (glBindBuffer (VBO)); 
// 3 ] Bind IBO        (glBindBuffer (IBO)); 

// 4 ] Set Pointers    (glVertexAttribPointer); 

// 5 ] Enable Pointers (glEnableVertexAttribArray); 

// 6 ] Active shader glUseProgram(ShaderID);
// For each mesh:
	// 4.4 ] Update Uniform(s)

	// 4.5 ] Active Textures
	// 4.6 ] Bind Textures
	// 4.7 ] Render mesh (model) (glDrawElements ili another method)
// 5 ] Disable everything
void Model::TerrainModel::render()
{
	m_terrainShaderIf->render(m_VAO, m_cameraIf, m_modelMatrix, m_gpuObjectTextureIf->getTextureStructVec()[0], numInd);
};


// LOAD PNG Texture
GLuint Model::TerrainModel::loadTexturePNG(const char* filename) {
	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN; //pointer to the image, once loaded
	FIBITMAP* dib(0);                    //pointer to the image data
	BYTE* bits(0);                       //image width and height
	unsigned int width(0), height(0);    //OpenGL's image ID to map to
	GLuint gl_texID;

	fif = FreeImage_GetFileType(filename, 0);
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);

	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);

	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

	// Novo
	RGBQUAD color;
	FreeImage_GetPixelColor(dib, 20, 20, &color);
	int heightImag = FreeImage_GetHeight(dib);

	//generate an OpenGL texture ID for this texture
	glGenTextures(1, &gl_texID);
	//bind to the new texture ID
	glBindTexture(GL_TEXTURE_2D, gl_texID);
	//store the texture data for OpenGL use

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits); // bits = imageData
																								// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmpWidth, bmpHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -1.5);

	//Free FreeImage's copy of the data
	FreeImage_Unload(dib);

	//return success
	return gl_texID;
};


void Model::TerrainModel::cmdPrompt(const std::string& arg0)
{
	std::cout << "TerrainModel: " << m_name << std::endl;
}
