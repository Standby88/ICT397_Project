#include "Model.h"
#include "GameObject3D.h"
Model::Model()
{

}

glm::mat4 Model::aiToGlm(aiMatrix4x4 ai_matr)
{
	glm::mat4 result;
	result[0].x = ai_matr.a1; result[0].y = ai_matr.b1; result[0].z = ai_matr.c1; result[0].w = ai_matr.d1;
	result[1].x = ai_matr.a2; result[1].y = ai_matr.b2; result[1].z = ai_matr.c2; result[1].w = ai_matr.d2;
	result[2].x = ai_matr.a3; result[2].y = ai_matr.b3; result[2].z = ai_matr.c3; result[2].w = ai_matr.d3;
	result[3].x = ai_matr.a4; result[3].y = ai_matr.b4; result[3].z = ai_matr.c4; result[3].w = ai_matr.d4;

	return result;
}


void Model::boneTransform(double time_in_sec, vector<aiMatrix4x4>& transforms)
{
	aiMatrix4x4 identity_matrix; // = mat4(1.0f);

	double time_in_ticks = time_in_sec * ticks_per_second;
	float animation_time = fmod(time_in_ticks, scene->mAnimations[0]->mDuration); 
																				  

	readNodeHierarchy(animation_time, scene->mRootNode, identity_matrix);

	transforms.resize(m_num_bones);

	for (uint i = 0; i < m_num_bones; i++)
	{
		transforms[i] = m_bone_matrices[i].final_world_transform;
	}
}

void Model::readNodeHierarchy(float p_animation_time, const aiNode * p_node, const aiMatrix4x4 parent_transform)
{

	string node_name(p_node->mName.data);

	const aiAnimation* animation = scene->mAnimations[0];
	aiMatrix4x4 node_transform = p_node->mTransformation;

	const aiNodeAnim* node_anim = findNodeAnim(animation, node_name); 

	if (node_anim)
	{

		//scaling
		//aiVector3D scaling_vector = node_anim->mScalingKeys[2].mValue;
		aiVector3D scaling_vector = calcInterpolatedScaling(p_animation_time, node_anim);
		aiMatrix4x4 scaling_matr;
		aiMatrix4x4::Scaling(scaling_vector, scaling_matr);

		//rotation
		//aiQuaternion rotate_quat = node_anim->mRotationKeys[2].mValue;
		aiQuaternion rotate_quat = calcInterpolatedRotation(p_animation_time, node_anim);
		aiMatrix4x4 rotate_matr = aiMatrix4x4(rotate_quat.GetMatrix());

		//translation
		//aiVector3D translate_vector = node_anim->mPositionKeys[2].mValue;
		aiVector3D translate_vector = calcInterpolatedPosition(p_animation_time, node_anim);
		aiMatrix4x4 translate_matr;
		aiMatrix4x4::Translation(translate_vector, translate_matr);

		if (string(node_anim->mNodeName.data) == string("Head"))
		{
			aiQuaternion rotate_head = aiQuaternion(rotate_head_xz.w, rotate_head_xz.x, rotate_head_xz.y, rotate_head_xz.z);

			node_transform = translate_matr * (rotate_matr * aiMatrix4x4(rotate_head.GetMatrix())) * scaling_matr;
		}
		else
		{
			node_transform = translate_matr * rotate_matr * scaling_matr;
		}

	}

	aiMatrix4x4 global_transform = parent_transform * node_transform;

	
	if (m_bone_mapping.find(node_name) != m_bone_mapping.end()) // true if node_name exist in bone_mapping
	{
		uint bone_index = m_bone_mapping[node_name];
		m_bone_matrices[bone_index].final_world_transform = m_global_inverse_transform * global_transform * m_bone_matrices[bone_index].offset_matrix;
	}

	for (uint i = 0; i < p_node->mNumChildren; i++)
	{
		readNodeHierarchy(p_animation_time, p_node->mChildren[i], global_transform);
	}

}

const aiNodeAnim * Model::findNodeAnim(const aiAnimation * p_animation, const string p_node_name)
{
	// channel in animation contains aiNodeAnim (aiNodeAnim its transformation for bones)
	// numChannels == numBones
	for (uint i = 0; i < p_animation->mNumChannels; i++)
	{
		const aiNodeAnim* node_anim = p_animation->mChannels[i]; 
		if (string(node_anim->mNodeName.data) == p_node_name)
		{
			return node_anim;
		}
	}

	return nullptr;
}

aiVector3D Model::calcInterpolatedScaling(float p_animation_time, const aiNodeAnim * p_node_anim)
{
	if (p_node_anim->mNumScalingKeys == 1) 
	{
		return p_node_anim->mScalingKeys[0].mValue;
	}

	uint scaling_index = findScaling(p_animation_time, p_node_anim);
	uint next_scaling_index = scaling_index + 1; 

												 
	float delta_time = (float)(p_node_anim->mScalingKeys[next_scaling_index].mTime - p_node_anim->mScalingKeys[scaling_index].mTime);
	
	float  factor = (p_animation_time - (float)p_node_anim->mScalingKeys[scaling_index].mTime) / delta_time;

	aiVector3D start = p_node_anim->mScalingKeys[scaling_index].mValue;
	aiVector3D end = p_node_anim->mScalingKeys[next_scaling_index].mValue;
	aiVector3D delta = end - start;

	return start + factor * delta;
}

uint Model::findRotation(float p_animation_time, const aiNodeAnim * p_node_anim)
{
	for (uint i = 0; i < p_node_anim->mNumPositionKeys - 1; i++) 
	{
		if (p_animation_time < (float)p_node_anim->mPositionKeys[i + 1].mTime) 
		{
			return i;
		}
	}
	return 0;
}

uint Model::findScaling(float p_animation_time, const aiNodeAnim * p_node_anim)
{
	
	for (uint i = 0; i < p_node_anim->mNumScalingKeys - 1; i++) 
	{
		if (p_animation_time < (float)p_node_anim->mScalingKeys[i + 1].mTime) 
		{
			return i;
		}
	}

	return 0;
}

aiQuaternion Model::calcInterpolatedRotation(float p_animation_time, const aiNodeAnim * p_node_anim)
{
	if (p_node_anim->mNumRotationKeys == 1) 
	{
		return p_node_anim->mRotationKeys[0].mValue;
	}

	uint rotation_index = findRotation(p_animation_time, p_node_anim); 
	uint next_rotation_index = rotation_index + 1; 


	float delta_time = (float)(p_node_anim->mRotationKeys[next_rotation_index].mTime - p_node_anim->mRotationKeys[rotation_index].mTime);
	
	float factor = (p_animation_time - (float)p_node_anim->mRotationKeys[rotation_index].mTime) / delta_time;

	//cout << "p_node_anim->mRotationKeys[rotation_index].mTime: " << p_node_anim->mRotationKeys[rotation_index].mTime << endl;
	//cout << "p_node_anim->mRotationKeys[next_rotaion_index].mTime: " << p_node_anim->mRotationKeys[next_rotation_index].mTime << endl;
	//cout << "delta_time: " << delta_time << endl;
	//cout << "animation_time: " << p_animation_time << endl;
	//cout << "animation_time - mRotationKeys[rotation_index].mTime: " << (p_animation_time - (float)p_node_anim->mRotationKeys[rotation_index].mTime) << endl;
	//cout << "factor: " << factor << endl << endl << endl;

	aiQuaternion start_quat = p_node_anim->mRotationKeys[rotation_index].mValue;
	aiQuaternion end_quat = p_node_anim->mRotationKeys[next_rotation_index].mValue;

	return nlerp(start_quat, end_quat, factor);
}

aiQuaternion Model::nlerp(aiQuaternion a, aiQuaternion b, float blend)
{
	//cout << a.w + a.x + a.y + a.z << endl;
	a.Normalize();
	b.Normalize();

	aiQuaternion result;
	float dot_product = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	float one_minus_blend = 1.0f - blend;

	if (dot_product < 0.0f)
	{
		result.x = a.x * one_minus_blend + blend * -b.x;
		result.y = a.y * one_minus_blend + blend * -b.y;
		result.z = a.z * one_minus_blend + blend * -b.z;
		result.w = a.w * one_minus_blend + blend * -b.w;
	}
	else
	{
		result.x = a.x * one_minus_blend + blend * b.x;
		result.y = a.y * one_minus_blend + blend * b.y;
		result.z = a.z * one_minus_blend + blend * b.z;
		result.w = a.w * one_minus_blend + blend * b.w;
	}

	return result.Normalize();
}

aiVector3D Model::calcInterpolatedPosition(float p_animation_time, const aiNodeAnim * p_node_anim)
{
	if (p_node_anim->mNumPositionKeys == 1) 
	{
		return p_node_anim->mPositionKeys[0].mValue;
	}

	uint position_index = findPosition(p_animation_time, p_node_anim);
	uint next_position_index = position_index + 1; 


	float delta_time = (float)(p_node_anim->mPositionKeys[next_position_index].mTime - p_node_anim->mPositionKeys[position_index].mTime);

	float factor = (p_animation_time - (float)p_node_anim->mPositionKeys[position_index].mTime) / delta_time;

	aiVector3D start = p_node_anim->mPositionKeys[position_index].mValue;
	aiVector3D end = p_node_anim->mPositionKeys[next_position_index].mValue;
	aiVector3D delta = end - start;

	return start + factor * delta;
}

uint Model::findPosition(float p_animation_time, const aiNodeAnim * p_node_anim)
{
	for (uint i = 0; i < p_node_anim->mNumPositionKeys - 1; i++) 
	{
		if (p_animation_time < (float)p_node_anim->mPositionKeys[i + 1].mTime) 
		{
			return i;
		}
	}
	return 0;
}

Model::Model(std::string path)
{
	this->loadModel(path);
	m_path = path;
}

void Model::Draw(Shader shader)
{
	std::vector<aiMatrix4x4> transforms;
	if (scene->HasAnimations() == true)
	{
		boneTransform((double)FrameTime::getInstance()->getElapsedTime() , transforms);

		for (int i = 0; i < transforms.size(); i++)
		{
			glUniformMatrix4fv(m_bone_location[i], 1, GL_TRUE, (const GLfloat*)&transforms[i]);
		}
	}
	
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
		.addFunction("initShdaer", &Model::initShaders)
		.endClass()
		.endNamespace();
}

void Model::DrawAnimtated(Shader & s, GameObject3D * parentGObj)
{

	glUniformMatrix4fv(glGetUniformLocation(s.Program, "gBones"), parentGObj->skeleton.boneMats.size(), GL_FALSE, glm::value_ptr(parentGObj->skeleton.boneMats[0]));
	for (GLuint i = 0; i < this->m_meshes.size(); i++)
	{
		this->m_meshes[i].DrawCharacter(s, parentGObj);
	}
}

void Model::initShaders(Shader * s)
{
	for (uint i = 0; i < MAX_BONES; i++) // get location all matrices of bones
	{
		string name = "bones[" + to_string(i) + "]";// name like in shader
		m_bone_location[i] = glGetUniformLocation(s->Program, name.c_str());
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

	m_RootNode = scene->mRootNode;
	m_global_inverse_transform = scene->mRootNode->mTransformation;
	m_global_inverse_transform.Inverse();
	if (scene->HasAnimations() == true)
	{
		if (scene->mAnimations[0]->mTicksPerSecond != 0.0)
		{
			ticks_per_second = scene->mAnimations[0]->mTicksPerSecond;
		}
		else
		{
			ticks_per_second = 25.0f;
		}
		cout << "scene->HasAnimations() 1: " << scene->HasAnimations() << endl;
		cout << "scene->mNumMeshes 1: " << scene->mNumMeshes << endl;
		cout << "scene->mAnimations[0]->mNumChannels 1: " << scene->mAnimations[0]->mNumChannels << endl;
		cout << "scene->mAnimations[0]->mDuration 1: " << scene->mAnimations[0]->mDuration << endl;
		cout << "scene->mAnimations[0]->mTicksPerSecond 1: " << scene->mAnimations[0]->mTicksPerSecond << endl << endl;
	}
	



	processNode(m_RootNode, scene);
	/*
	for (uint i = 0; i < scene->mAnimations[0]->mNumChannels; i++)
	{
		cout << scene->mAnimations[0]->mChannels[i]->mNodeName.C_Str() << endl;
	}*/



	/*


	if (scene != nullptr)
	{
		error = false;
		m_RootNode = scene->mRootNode;
		recursiveNodeProcess(m_RootNode);
		AnimNodeProcess();
		globalInverseTransform = glm::inverse(AiToGLMMat4(m_RootNode->mTransformation));
		// Process ASSIMP's root node recursively
		this->processNode(m_RootNode, scene);


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
		}
			
	}
	else
	{
		error = true;
		std::cout << "Unable to load mesh: " <<path << std::endl;
	}
	*/
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
	// Data to fill and passed to a mesh
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
	vector<VertexBoneData> bones_id_weights_for_each_vertex;
	//used to store bone weights and ids
	bones_id_weights_for_each_vertex.resize(mesh->mNumVertices);

	// Walk through each of the mesh's vertices
	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
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
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// Retrieve all indices of the face and store them in the indices vector
		for (GLuint j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		bool exist = false;
		// 1. Diffuse material values
		vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		// 2. Specular material values
		vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	for (uint i = 0; i < mesh->mNumBones; i++)
	{
		uint bone_index = 0;
		string bone_name(mesh->mBones[i]->mName.data);
		cout << mesh->mBones[i]->mName.data << endl;
		if (m_bone_mapping.find(bone_name) == m_bone_mapping.end())
		{
			bone_index = m_num_bones;
			m_num_bones++;
			BoneMatrix bi;
			m_bone_matrices.push_back(bi);
			m_bone_matrices[bone_index].offset_matrix = mesh->mBones[i]->mOffsetMatrix;
			m_bone_mapping[bone_name] = bone_index;
		}
		else
		{
			bone_index = m_bone_mapping[bone_name];
		}
		for (uint j = 0; j < mesh->mBones[i]->mNumWeights; j++)
		{
			uint vertex_id = mesh->mBones[i]->mWeights[j].mVertexId; 
			float weight = mesh->mBones[i]->mWeights[j].mWeight;
			bones_id_weights_for_each_vertex[vertex_id].addBoneData(bone_index, weight);

		}
	}
	/*
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
	*/
	

	// Process assimp materials
	


	
	// Return a mesh object created from the extracted mesh data
	return Mesh(vertices, indices, textures, bones_id_weights_for_each_vertex);
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