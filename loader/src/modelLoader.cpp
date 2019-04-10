#include "modelLoader.h"

#include "factory.h"

#include "error.h"


Loader::ModelLoader::ModelLoader(Common::Error& err, const std::string& name) : m_name(name)
{
	std::cout << "ModelLoader created!" << std::endl;

	postInit();
}


Loader::ModelLoader::~ModelLoader()
{
	std::cout << "TemplateDefault destructor called!" << std::endl;
}


const std::string& Loader::ModelLoader::getName()
{
	return m_name;
}


void Loader::ModelLoader::preInit()
{
	// Get from DB
}


void Loader::ModelLoader::postInit()
{
	std::cout << "postInit function called!" << std::endl;
	// Create ModelGPUObject - Get object_name from DB
	
	// Create VAO
		// Create VBO and IBO foreach mesh (vector of GLuint)

	// Store ModelGPUObject in Factory (Container)


	/*
	CF.getStringFromDB(modelFolder, "modelName", modelName);
	modelName += ".3ds";
	//modelName += ".obj";
	*/

	loadModel();
}


void Loader::ModelLoader::loadModel()
{
	std::cout << "loadModel function called!" << std::endl;
	Common::Error err;
	// CREATE MODEL

	std::string modelStr("_vanquish/vanquish.3ds");
	
	Assimp::Importer Importer;
	pScene = Importer.ReadFile(modelStr.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (pScene)
	{
		std::string vanquish("vanquish");
		m_GPUObjectIf = std::make_shared<GPUObject::ModelGPUObject>(err, "vanquish");

		std::cout << " xxx INIT OK" << std::endl;		
		initScene(pScene);
	}
	else
	{
		// CommonFunctions::INFOCMD(LOG "ERROR parsing: " + modelFolder + modelName + ". " + Importer.GetErrorString());
		std::cout << " xxx INIT NOK" << std::endl;
	}	
}


void Loader::ModelLoader::initScene(const aiScene* _pScene)
{
	// CREATE GPU MODEL
	// Create VAO for whole Model
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	std::cout << " xxx VAO = " << VAO  << "_pScene->mNumMeshes = " << _pScene->mNumMeshes << std::endl;
	m_GPUObjectIf->setVAO(VAO);

	// START CREATING MESHes
	// Create VBO and IBO for each Mesh in Model
	for (unsigned int i = 0; i < _pScene->mNumMeshes; ++i)
	{
		const aiMesh* paiMesh = _pScene->mMeshes[i];

		initMesh(i, paiMesh);
	}

	Common::Factory::getInstance().storeInContainer("GPUObjectIf", m_GPUObjectIf);
	std::cout << " NUM OF INSTANCES IN Loader: " << Common::Factory::getInstance().getGPUObjectIf("vanquish").use_count() << "\n";
}


// MESH
void Loader::ModelLoader::initMesh(GLuint _index, const aiMesh* _paiMesh)
{
	std::vector<Vert>         vertices; // PER MESH [position (x, y, z), texture(u, v), noraml(x, y, z)]
	std::vector<unsigned int> indices;  // PER MESH

	glm::vec3* positionCoord = new glm::vec3(0.0f);
	glm::vec3* textureCoord  = new glm::vec3(0.0f);
	glm::vec3* normalCoord   = new glm::vec3(0.0f);

	for (unsigned int i = 0; i < _paiMesh->mNumVertices; i++)
	{
		// Positions
		positionCoord->x = _paiMesh->mVertices[i].x;
		positionCoord->y = _paiMesh->mVertices[i].y;
		positionCoord->z = _paiMesh->mVertices[i].z;
		// Texture
		textureCoord->x = _paiMesh->mTextureCoords[0][i].x;
		textureCoord->y = _paiMesh->mTextureCoords[0][i].y;
		// Normals
		normalCoord->x = _paiMesh->mNormals[i].x;
		normalCoord->y = _paiMesh->mNormals[i].y;
		normalCoord->z = _paiMesh->mNormals[i].z;

		Vert v(glm::vec3(positionCoord->x, positionCoord->y, positionCoord->z), // in vec3 position
			   glm::vec2(textureCoord->x, textureCoord->y),                     // in vec2 textureCoordinates
			   glm::vec3(normalCoord->x, normalCoord->y, normalCoord->z));      // in vec3 normal

		vertices.push_back(v);
	}

	delete positionCoord;
	delete textureCoord;
	delete normalCoord;

	for (unsigned int i = 0; i < _paiMesh->mNumFaces; i++)
	{
		const aiFace& Face = _paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		indices.push_back(Face.mIndices[0]);
		indices.push_back(Face.mIndices[1]);
		indices.push_back(Face.mIndices[2]);
	}

	// For each Mesh in Model - Create  VBO and IBO
	GLuint VBO;
	glGenBuffers(1, &VBO);
	std::cout << " xxx VBO = " << VBO << std::endl;
	m_GPUObjectIf->setVBO(VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * vertices.size(), &vertices[0], GL_STATIC_DRAW); // sizeof(Vert) = 32

	GLuint IBO;
	glGenBuffers(1, &IBO);
	std::cout << " xxx IBO = " << IBO << std::endl;
	m_GPUObjectIf->setIBO(IBO);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
}
