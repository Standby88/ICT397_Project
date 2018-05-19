#include "Model.h"

Model::Model()
{

}

Model::Model(std::string path)
{
	this->loadModel(path);
	m_path = path;
}

void Model::Draw(Shader shader)
{
	for (GLuint i = 0; i < this->m_meshes.size(); i++)
	{
		this->m_meshes[i].Draw(shader);
	}
}
std::string Model::getName()
{
	return m_path;
}

void Model::scriptRegister(lua_State * L)
{
	using namespace luabridge;
	getGlobalNamespace(L)
		.beginNamespace("MOD")
		.beginClass<Model>("Model")
		.addConstructor<void(*) (void)>()
		.addConstructor<void(*) (GLchar *)>()
		.addFunction("Draw", &Model::Draw)
		.addFunction("getName", &Model::getName)
		.endClass()
		.endNamespace();
}

void Model::loadModel(string path)
{
	// Read file via ASSIMP
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	// Check for errors
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return;
	}
	// Retrieve the directory path of the filepath
	this->m_directory = path.substr(0, path.find_last_of('/'));

	// Process ASSIMP's root node recursively
	this->processNode(scene->mRootNode, scene);
}

// Processes an assimp node in a recursive fashion. 
//Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
void Model::processNode(aiNode* node, const aiScene* scene)
{
	// Process each mesh located in the current node
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		// The node object only contains indices to index the actual objects in the scene.
		// The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

		this->m_meshes.push_back(this->processMesh(mesh, scene));
	}

	// After we've processed all of the meshes then we recursively process each child node
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
	int WEIGHTS_PER_VERTEX = 4;
	int boneArraysSize = mesh->mNumVertices*WEIGHTS_PER_VERTEX;
	// Data to fill and passed to a mesh
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
	//used to store bone weights and ids
	std::vector<int> boneIDs;
	boneIDs.resize(boneArraysSize);
	std::vector<float> boneWeights;
	boneWeights.resize(boneArraysSize);


	// Walk through each of the mesh's vertices
	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		//placeholder vector since assimp's vector doesn't play nice with V3
		V3 vector;

						  // Positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		// Normals
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;

		// if tex coords process them otherwise set tex coords to zero
		if (mesh->mTextureCoords[0])
		{
			V2 vec;
			// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
		{
			vertex.TexCoords = V2(0.0f, 0.0f);
		}

		vertices.push_back(vertex);
	}

	for (int i = 0; i<mesh->mNumBones; i++)
	{
		//(above) NOTE THAT mesh IS NOT OF TYPE Mesh,
		//IT IS A POINTER TO THE CURRENT MESH, OF TYPE aiMesh

		aiBone* aiBone = mesh->mBones[i]; //CREATING A POINTER TO THE CURRENT BONE
										  //IT'S IMPORTANT TO NOTE THAT i IS JUST THE ID OF THE CURRENT BONE.

		for (int j = 0; j<aiBone->mNumWeights; j++)
		{
			aiVertexWeight weight = aiBone->mWeights[j];

			//THIS WILL TELL US WHERE, IN OUR ARRAY, TO START READING THE VERTEX'S WEIGHTS
			unsigned int vertexStart = weight.mVertexId * WEIGHTS_PER_VERTEX;

			//HERE WE'LL ACTUALLY FILL THE ARRAYS, WITH BOTH INDICES AND WEIGHTS.
			for (int k = 0; k<WEIGHTS_PER_VERTEX; k++)
			{
				if (boneWeights.at(vertexStart + k) == 0)
				{
					//(above) IF THE CURRENT BONE WEIGHT IS EQUAL TO 0,
					//THEN IT HASN'T BEEN FILLED YET WITH AN ACTUAL WEIGHT.
					boneWeights.at(vertexStart + k) = weight.mWeight;
					boneIDs.at(vertexStart + k) = i; //REMEMBER THAT i IS JUST THE ID OF THE CURRENT BONE.

													 //NOTE THAT data IS JUST AN ARRAY OF TYPE Vertex, WHERE I STORE ALL OF THE VERTEX INFO.
													 //EACH Vertex CLASS HAS SPACE FOR A POSITION, A UV, A NORMAL, AND 4 INDICES, AND 4 WEIGHTS.
													 //EACH Mesh IS THEN CREATED WITH THIS THIS ARRAY OF Vertex (THIS ARRAY BEING data).

					vertices.at(weight.mVertexId).id[k] = i;
					//SETTING THE ID
					//AT k, OF
					//THE VERTEX AT THIS WEIGHT'S ID,
					//TO THE CURRENT BONE ID.

					vertices.at(weight.mVertexId).weight[k] = weight.mWeight;
					//SETTING THE WEIGHT
					//AT k, OF
					//THE VERTEX AT THIS WEIGHT'S ID,
					//TO THIS WEIGHT'S WEIGHT.
					break;
				}
			}
		}
	}
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// Retrieve all indices of the face and store them in the indices vector
		for (GLuint j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	// Process assimp materials
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		// 1. Diffuse material values
		vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		// 2. Specular material values
		vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}


	
	// Return a mesh object created from the extracted mesh data
	return Mesh(vertices, indices, textures);
}

vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
{
	TextureManager texMan = TextureManager::GetTextureManager();
	vector<Texture> textures;

	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		// Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		GLboolean skip = false;

		for (GLuint j = 0; j < m_textures_loaded.size(); j++)
		{
			if (m_textures_loaded[j].path == str)
			{
				textures.push_back(m_textures_loaded[j]);
				skip = true; // A texture with the same filepath has already been loaded, continue to next one. (optimization)

				break;
			}
		}

		if (!skip)
		{   // If texture hasn't been loaded already, load it
			Texture texture;
			//texture.id = TextureFromFile(str.C_Str(), this->directory);
			string filename = string(str.C_Str());
			filename = this->m_directory + '/' + filename;
			//add the texture to the textureManager
			texMan.AddTexture(filename.c_str());
			//get the texture from the textureManager
			texture.id = texMan.GetTexture(filename.c_str());
			texture.type = typeName;
			texture.path = str;
			textures.push_back(texture);

			this->m_textures_loaded.push_back(texture);  // Store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
		}
	}

	return textures;
}