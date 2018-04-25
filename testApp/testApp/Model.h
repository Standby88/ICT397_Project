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

extern "C"
{
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include <LuaBridge.h>
#include <string>
#include <glm\glm.hpp>

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

private:
	std::string m_path;
	/*  Model Data  */
	vector<Mesh> m_meshes;
	string m_directory;
	vector<Texture> m_textures_loaded;	

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
	void processNode(aiNode* node, const aiScene* scene);

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