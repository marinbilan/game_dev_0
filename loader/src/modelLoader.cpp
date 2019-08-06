#include "modelLoader.h"

#include "factory.h"


Loader::ModelLoader::ModelLoader(const std::string& name) : m_name(name)
{
	postInit();
}


Loader::ModelLoader::~ModelLoader()
{
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
	loadModel();
}


void Loader::ModelLoader::loadModel()
{

	std::vector<std::string> GPUObjectModelVec;
	FACTORY.getDatabase()->getRest(m_name, "GPUObjectModel", GPUObjectModelVec);
	/*
	    modelLoader_0      GPUObjectModel      _vanquish/vanquish.3ds
		...
	*/

	for (auto GPUObjectModelString : GPUObjectModelVec)
	{
		// Get column
		FACTORY.getDatabase()->getAll21(GPUObjectModelString, "meshStructure", m_meshStructNameTempVec);
		/*
		    _vanquish/vanquish.3ds    meshStructure    name0
            _vanquish/vanquish.3ds    meshStructure    name1
			...
		*/

		// FOREACH MODEL STRING
		Assimp::Importer Importer;
		pScene = Importer.ReadFile(GPUObjectModelString.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

		if (pScene)
		{
			// CREATE GPU OBJECT //
			m_GPUObjectIf = std::make_shared<GPUObject::ModelGPUObject>(GPUObjectModelString);

			// Store created GPU object in factory container
			Common::Factory::getInstance().storeInContainer("GPUObjectIf", m_GPUObjectIf);

			initScene(pScene);
			// TODO: store GPU_Object in Factory and get that object from Model instance
		}
		else
		{
		}
	}

}


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
			name0    normalMap    false
			name1    normalMap    true
			...
		*/
		if (!normalMapString.compare("false"))
		{
		    const aiMesh* paiMesh = _pScene->mMeshes[i];
			initMesh(*it0, i, paiMesh);
			++it0;
		}
		else if(!normalMapString.compare("true"))
		{
			// Load NormalMap mesh
		}

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
