#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include <GL/glew.h>
#include "MathLib.h"
#include "SOIL2/SOIL2.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "TextureManager.h"

#include "Mesh.h"
#include "Bone.h"
extern "C"
{
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include <LuaBridge.h>
#include <string>


/**
* @class Model
* @brief Used to load model and store model data for it to be drawn
*
* @author Alex
* @version 1
* @date
*
* @todo
*
* @bug
*/
class GameObject3D;
class Model
{
public:

	/**
	* @brief default Constructor
	*/
	Model();


	/*  Functions   */
	/**
	* @brief Constructor, expects a filepath to a 3D model.
	*/
	Model(std::string path);


	/**
	* @brief Draws the model, and thus all its meshes
	*/
	void Draw(Shader shader);
	
	/**
	* @brief returns path of model
	*@return string m_path
	*/
	std::string getName();

	/**
	* @brief expose functions to lua
	*@param lua_State * L
	*/
	static void scriptRegister(lua_State * L);
	Mesh& getFirstMesh()
	{
		return m_meshes.at(0);
	}
	bool checkMeshSize()
	{
		if (m_meshes.size() != 0)
			return true;
		else
		{
			return false;
		}
	}
	void DrawAnimtated(Shader&s, GameObject3D * parentGObj);
private:
	std::vector<aiNode*> ai_nodes;
	std::vector<aiNodeAnim*> ai_nodes_anim;
	void recursiveNodeProcess(aiNode* node);
	void AnimNodeProcess();
	const aiScene *scene;
	std::string m_path;
	bool error;
	/*  Model Data  */
	vector<Mesh> m_meshes;
	string m_directory;
	vector<Texture> m_textures_loaded;	
	aiNode* m_RootNode;
	glm::mat4 globalInverseTransform;
	std::vector<Bone> bones;
	Bone* FindBone(std::string name);
	aiNode* FindAiNode(std::string name);
	aiNodeAnim* FindAiNodeAnim(std::string name);
	int FindBoneIDByName(std::string name)
	{
		for (int i = 0; i < bones.size(); i++)
		{
			if (bones.at(i).name == name)
				return i;
		}
		//This function finds the position of a certain bone within our bones vector.
		//This position is equal to the bone's ID, which is vital to determining the
		//rigging of our model within the vertex shader.
		return -1;    //In case we don't find a bone ID, we return -1.
					  //Just to avoid any confusion later on as to whether or not the
					  //ID was found. (It serves the same purpose as returning nullptr).
	}
	/**
    * @brief Loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
	*
	*@param string path
	*/
	void loadModel(string path);

	/**
	* @brief  Processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	*
	*@param aiNode* node, const aiScene* scene
	*/
	void processNode(aiNode* node, const aiScene* scene, bool error);

	/**
	* @brief process mesh data
	*
	*@param aiNode* node, const aiScene* scene
	*@return Mesh
	*/
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);

	/**
	* @brief load material textures
	*
	*@param aiMaterial *mat, aiTextureType type, string typeName
	*@return vector<texture>
	*/
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};