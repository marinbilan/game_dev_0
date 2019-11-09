#include "modelLoader.h"

#include "factory.h"


Loader::ModelLoader::ModelLoader(const std::string& name) : m_name(name)
{

}


Loader::ModelLoader::ModelLoader(const std::string& dbPath, const std::string& name) :
	m_dbPath(dbPath),
	m_name(name)
{
	m_dbPathWithName = m_dbPath + m_name + "_";

	std::string instName = m_dbPathWithName + m_name;
	FACTORY.getLog()->LOGFILE(LOG "ModelLoader: " + m_name + " created.");
}


Loader::ModelLoader::~ModelLoader()
{
}


const std::string& Loader::ModelLoader::getName()
{
	return m_name;
}


void Loader::ModelLoader::preInitialization()
{
	// ex: _src/models/
	std::string modelsPath = m_dbPathWithName + "modelsPath";
	FACTORY.getDatabase()->getStringsFromDB(modelsPath, m_vecModelsPath);

	// ex: vanquish.3ds model0.3ds model1.3ds ...
	std::string modelsForLoad = m_dbPathWithName + "modelsForLoad";
	std::vector<std::string> vecModelsForLoad;
	FACTORY.getDatabase()->getStringsFromDB(modelsForLoad, vecModelsForLoad);

	loadModelNew(vecModelsForLoad);
}


void Loader::ModelLoader::postInitialization()
{

}

// TODO: remove
void Loader::ModelLoader::loadModel()
{
	std::vector<std::string> vec0;
	std::vector<std::string> vec1;
	FACTORY.getDatabase()->getColumnOfStrings22(m_name, "GPUObjectModel", vec0, vec1);
	/*
	                                   vec0                  vec1
	modelLoader_0    GPUObjectModel    (vanquishGPUModel)    (_vanquish/vanquish.3ds)
	modelLoader_0    GPUObjectModel    (cubeGPUModel)        (_src/models/cube.3ds)
	...
    */
	// PRINT
	// ----
		std::vector<std::string>::iterator it1 = vec1.begin();
		for (auto s : vec0)
		{
			FACTORY.getLog()->LOGFILE(LOG "> " + m_name + "    GPUObjectModel    " + s + "    " + *it1);
			++it1;
		}
	// ----

	std::vector<std::string>::iterator itVec1 = vec1.begin(); // vec1
	/*
		Iterate ovec vec0 and load vec1 models
	*/
	for (auto GPUObjectModelString : vec0) // vec0
	{
		// Get column
		FACTORY.getDatabase()->getColumn21(GPUObjectModelString, "meshStructure", m_meshStructNameTempVec);
		/*
		    vec0                                 m_meshStructNameTempVec
		    vanquishGPUModel    meshStructure    (vanName0)
            vanquishGPUModel    meshStructure    (vanName1)
			...
		*/
		// PRINT
        // ----
			for (auto s : m_meshStructNameTempVec)
			{
				FACTORY.getLog()->LOGFILE(LOG "> " + GPUObjectModelString + "    meshStructure    " + s);
			}
		// ----

		// FOREACH MODEL STRING
		Assimp::Importer Importer;
		pScene = Importer.ReadFile((*itVec1).c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

		if (pScene)
		{
			// CREATE GPU OBJECT //
			m_GPUObjectIf = std::make_shared<GPUObject::ModelGPUObject>(GPUObjectModelString);

			// Store created GPU object in factory container
			Common::Factory::getInstance().storeInContainer("GPUObjectIf", m_GPUObjectIf);

			initScene(pScene);
		}
		else
		{
		}

		++itVec1;
		// std::cout << " MESH VECTOR SIZE BEFORE: " << m_meshStructNameTempVec.size() << '\n';
		m_meshStructNameTempVec.clear();
		// std::cout << " MESH VECTOR SIZE AFTER: " << m_meshStructNameTempVec.size() << '\n';
	}
}


void Loader::ModelLoader::loadModelNew(const std::vector<std::string>& vecModelsForLoad)
{
	for (auto s : vecModelsForLoad)
	{
		// ex: def nm def nm  def nm
		std::string meshAtribsKey = m_dbPathWithName + s + "_meshAttribs";
		FACTORY.getDatabase()->getStringsFromDB(meshAtribsKey, m_vecMeshAttribs);

		Assimp::Importer Importer;
		// ex: _src/models/vanquish.3ds
		std::string modelPath = m_vecModelsPath[0] + s;
		pScene = Importer.ReadFile(modelPath.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

		if (pScene)
		{
			// CREATE GPU OBJECT //
			m_GPUObjectIf = std::make_shared<GPUObject::ModelGPUObject>(s);

			// Store created GPU object in factory container
			Common::Factory::getInstance().storeInContainer("GPUObjectIf", m_GPUObjectIf);

			initSceneNew(pScene);
		}
		else
		{
		}

		m_vecMeshAttribs.clear();
	}
}

// TODO: remove
void Loader::ModelLoader::initScene(const aiScene* _pScene)
{
	// CREATE GPU MODEL
	GLuint VAO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	m_VAO = VAO;

	// START CREATING MESHes
	// Create VBO and IBO for each Mesh in Model
	std::vector<std::string>::iterator it0 = m_meshStructNameTempVec.begin();

	std::string normalMapString;
	for (unsigned int i = 0; i < _pScene->mNumMeshes; ++i)
	{
		FACTORY.getDatabase()->getStringFromDB(*it0, "normalMap", normalMapString);
		/*
		                             normalMapString
			vanName0    normalMap    (false)
			...
			vanName1    normalMap    (true)
			...
		*/
		FACTORY.getLog()->LOGFILE(LOG "> " + *it0 + "    normalMap    " + normalMapString);

		if (!normalMapString.compare("false"))
		{
		    const aiMesh* paiMesh = _pScene->mMeshes[i];
			initMesh(*it0, i, paiMesh);
			++it0;
		}
		else if(!normalMapString.compare("true"))
		{
			// Load NormalMap mesh
			const aiMesh* paiMesh = _pScene->mMeshes[i];
			initNormalMapMesh(*it0, i, paiMesh);
			++it0;
		}

	}
}


void Loader::ModelLoader::initSceneNew(const aiScene* _pScene)
{
	// CREATE GPU MODEL
	GLuint VAO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	m_VAO = VAO;
	// TODO: Change tempMeshName
	std::string tempMeshName("NoName");
	std::vector<std::string>::iterator it = m_vecMeshAttribs.begin();
	for (unsigned int i = 0; i < _pScene->mNumMeshes; ++i)
	{
		if (!(*it).compare("def"))
		{
			const aiMesh* paiMesh = _pScene->mMeshes[i];
			initMesh(tempMeshName, i, paiMesh);
		}
		else if (!(*it).compare("np"))
		{
			// Load NormalMap mesh
			const aiMesh* paiMesh = _pScene->mMeshes[i];
			initNormalMapMesh(tempMeshName, i, paiMesh);
		}
		++it;
	}
}


// MESH
void Loader::ModelLoader::initMesh(const std::string& meshName, GLuint _index, const aiMesh* _paiMesh)
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

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * vertices.size(), &vertices[0], GL_STATIC_DRAW); // sizeof(Vert) = 32

	GLuint IBO;
	glGenBuffers(1, &IBO);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// Store Stuff
 	GPUObject::MeshStructure tempMesh(meshName);
	tempMesh.m_VAO = m_VAO;
	tempMesh.m_VBO = VBO;
	tempMesh.m_IBO = IBO;
	tempMesh.m_NumOfInds = vertices.size();

	m_GPUObjectIf->setMeshInVec(tempMesh);

	// ----
	std::shared_ptr<GPUObject::MeshStructure> tempMeshShared = std::make_shared<GPUObject::MeshStructure>(meshName);
	tempMeshShared->m_VAO = m_VAO;;
	tempMeshShared->m_VBO = VBO;
	tempMeshShared->m_IBO = IBO;
	tempMeshShared->m_NumOfInds = vertices.size();
	// ----

	// Copy store in Factory
	FACTORY.storeInContainer(tempMeshShared);
}


// NORMAL MAP MESH
void Loader::ModelLoader::initNormalMapMesh(const std::string& meshName, GLuint _index, const aiMesh* _paiMesh)
{
	std::vector<VertNormalMap> vertices; // PER MESH [position (x, y, z), texture(u, v), noraml(x, y, z) tengent(x, y, z)]
	std::vector<unsigned int>  indices;  // PER MESH

	glm::vec3* positionCoord = new glm::vec3(0.0f);
	glm::vec2* textureCoord = new glm::vec2(0.0f);
	glm::vec3* normalCoord = new glm::vec3(0.0f);
	glm::vec3* tangentCoord = new glm::vec3(0.0f);

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
		// Tangents
		tangentCoord->x = _paiMesh->mTangents[i].x;
		tangentCoord->y = _paiMesh->mTangents[i].y;
		tangentCoord->z = _paiMesh->mTangents[i].z;

		VertNormalMap v(glm::vec3(positionCoord->x, positionCoord->y, positionCoord->z), // in vec3 position
			glm::vec2(textureCoord->x, textureCoord->y),                                 // in vec2 textureCoordinates
			glm::vec3(normalCoord->x, normalCoord->y, normalCoord->z),                   // in vec3 normal
			glm::vec3(tangentCoord->x, tangentCoord->y, tangentCoord->z));               // in vec3 tangent       

		vertices.push_back(v);
	}

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

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertNormalMap) * vertices.size(), &vertices[0], GL_STATIC_DRAW); // sizeof(Vert) = 32

	GLuint IBO;
	glGenBuffers(1, &IBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// vectorOfMeshes[_index].numIndices = indices.size(); // For each mesh! Important for rendering!

	// Store Stuff
	GPUObject::MeshStructure tempMesh(meshName);
	tempMesh.m_VAO = m_VAO;
	tempMesh.m_VBO = VBO;
	tempMesh.m_IBO = IBO;
	tempMesh.m_NumOfInds = vertices.size();

	m_GPUObjectIf->setMeshInVec(tempMesh);

	// ----
	std::shared_ptr<GPUObject::MeshStructure> tempMeshShared = std::make_shared<GPUObject::MeshStructure>(meshName);
	tempMeshShared->m_VAO = m_VAO;;
	tempMeshShared->m_VBO = VBO;
	tempMeshShared->m_IBO = IBO;
	tempMeshShared->m_NumOfInds = vertices.size();
	// ----

	// Copy store in Factory
	FACTORY.storeInContainer(tempMeshShared);
}