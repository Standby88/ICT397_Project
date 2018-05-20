#include "Model.h"
#include "GameObject3D.h"
Model::Model()
{

}

Model::Model(std::string path)
{
	this->loadModel(path);
	m_path = path;
	m_meshes.at(0);
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

void Model::DrawAnimtated(Shader & s, GameObject3D * parentGObj)
{

	for (GLuint i = 0; i < this->m_meshes.size(); i++)
	{
		this->m_meshes[i].DrawCharacter(s, parentGObj);
	}
}

void Model::recursiveNodeProcess(aiNode * node)
{
	ai_nodes.push_back(node);

	for (int i = 0; i < node->mNumChildren; i++)
		recursiveNodeProcess(node->mChildren[i]);
}

void Model::AnimNodeProcess()
{
	if (scene->mNumAnimations == 0)
		return;

	for (int i = 0; i < scene->mAnimations[0]->mNumChannels; i++)
		ai_nodes_anim.push_back(scene->mAnimations[0]->mChannels[i]);

	//We only get data from the first mAnimation because 
	//Assimp crushes all of the animation data into one
	//large sequence of data known as mAnimation.
	//Assimp does not support multiple mAnimations, surprisingly.
}

Bone * Model::FindBone(std::string name)
{
	for (int i = 0; i < bones.size(); i++)
	{
		if (bones.at(i).name == name)
			return &bones.at(i);
	}
	//This function simply scans our vector bones and checks if
	//any name matches the name we're looking for, if it doesn't
	//find any, we return nullptr.
	//Keep in mind, the bones vector is empty at the point of writing this,
	//but when this function is called it will already be filled up.
	return nullptr;
}

aiNode * Model::FindAiNode(std::string name)
{
	for (int i = 0; i < ai_nodes.size(); i++)
	{
		if (ai_nodes.at(i)->mName.data == name)
			return ai_nodes.at(i);
	}
	//This function's purpose is identical, except that instead of Bones,
	//it's looking for an aiNode* inside our ai_nodes vector.
	//This vector has already been filled by our recursiveNodeProcess() function.
	return nullptr;
}

aiNodeAnim * Model::FindAiNodeAnim(std::string name)
{
	for (int i = 0; i < ai_nodes_anim.size(); i++)
	{
		if (ai_nodes_anim.at(i)->mNodeName.data == name)
			return ai_nodes_anim.at(i);
	}
	//This function finds the animation with the name we pass in, we called it
	//right after calling our recursiveNodeProcess() function, but this function
	//will only really come into play during the next tutorial, where we cover
	//the actual animation portion of skeletal animation.
	return nullptr;
}

void Model::loadModel(string path)
{
	// Read file via ASSIMP
	
	//scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	scene = importer.ReadFile(path, aiProcess_GenSmoothNormals | aiProcess_Triangulate |
		aiProcess_CalcTangentSpace | aiProcess_FlipUVs |
		aiProcess_JoinIdenticalVertices);
	// Check for errors
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return;
	}
	// Retrieve the directory path of the filepath
	this->m_directory = path.substr(0, path.find_last_of('/'));

	if (scene != nullptr)
	{
		error = false;
		m_RootNode = scene->mRootNode;
		recursiveNodeProcess(m_RootNode);
		AnimNodeProcess();
		globalInverseTransform = glm::inverse(AiToGLMMat4(m_RootNode->mTransformation));
		// Process ASSIMP's root node recursively
		this->processNode(m_RootNode, scene, error);


		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			for (int j = 0; j < scene->mMeshes[i]->mNumBones; j++)
			{
				std::cout << scene->mMeshes[i]->mNumBones << std::endl;
				//Here we're just storing the bone information that we loaded
				//with ASSIMP into the formats our Bone class will recognize.
				std::string b_name = scene->mMeshes[i]->mBones[j]->mName.data;
				glm::mat4 b_mat = glm::transpose(AiToGLMMat4(scene->mMeshes[i]->mBones[j]->mOffsetMatrix));

				//Just because I like debugging...
				std::cout << "Bone " << j << " " << b_name << std::endl;


				//Here we create a Bone Object with the information we've
				//gathered so far, but wait, there's more!
				Bone bone(&m_meshes.at(i), i, b_name, b_mat);
				//These next parts are simple, we just fill up the bone's
				//remaining data using the functions we defined earlier.
				bone.node = FindAiNode(b_name);
				bone.animNode = FindAiNodeAnim(b_name);
				if (bone.animNode == nullptr)
					std::cout << "No Animations were found for " + b_name << std::endl;

				//Finally, we push the Bone into our vector. Yay.
				
				bones.push_back(bone);

			}
		}
			
		//Now we have to fill up the remaining ... remaining data within the
		//bone object, specifically: the pointers to the bone's parent bone.
		for (int i = 0; i < bones.size(); i++)
		{
			//Here we cycle through the existing bones and match them up with
			//their parents, the code here is pretty self explanatory.
			std::string b_name = bones.at(i).name;
			std::string parent_name = FindAiNode(b_name)->mParent->mName.data;
			Bone* p_bone = FindBone(parent_name);

			bones.at(i).parent_bone = p_bone;
			if (p_bone == nullptr)
				std::cout << "Parent Bone for " << b_name << " does not exist (is nullptr)" << std::endl;
		}
		//Here we only need to give the first Mesh in meshes the skeleton data
		//because in order to initialize the GameObject that will encapsulate this
		//Mesh, we only need one skeleton. The GameObject will copy the skeleton
		//of the first Mesh in its meshes vector and use this as its own.
		//Did that not make sense?
		//Shit.
		//It will later on though, so don't worry.
		if (m_meshes.size() > 0)
		{
			m_meshes.at(0).sceneLoaderSkeleton.Init(bones, globalInverseTransform);
			
				std::cout<<"loadModel: " << &m_meshes.at(0).sceneLoaderSkeleton << std::endl;
				
				outMesh.push_back(m_meshes.at(0));
				outMesh.push_back(m_meshes.at(1));
		}
			
	}
	else
	{
		error = true;
		std::cout << "Unable to load mesh: " <<path << std::endl;
	}

}

// Processes an assimp node in a recursive fashion. 
//Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
void Model::processNode(aiNode* node, const aiScene* scene, bool error)
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
		this->processNode(node->mChildren[i], scene, error);
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