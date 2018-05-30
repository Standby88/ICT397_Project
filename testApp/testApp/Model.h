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
	* @param std::string
	*/
	Model(std::string path);

	///Default Destructor
	~Model() {};

	///uint variable for max number of bones
	static const uint MAX_BONES = 100;
	
	/**
	* @brief Initialises shaders for a model
	* @param Shader*
	* @return void
	*/
	void initShaders(Shader *s);

	/**
	* @brief Draws the model, and thus all its meshes
	*/
	void Draw(Shader shader);

	glm::mat4 aiToGlm(aiMatrix4x4 ai_matr);
	aiQuaternion nlerp(aiQuaternion a, aiQuaternion b, float blend);

	/**
	* @brief Loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
	*
	*@param std::string path
	*/
	void loadModel(std::string path);
	
	/**
	* @brief returns path of model
	* @return std::string m_path
	*/
	std::string getName();

	/**
	* @brief expose functions to lua
	* @param lua_State * L
	*/
	static void scriptRegister(lua_State * L);

private:
	///Assimp::Importer variable
	Assimp::Importer importer;
	///aiScene* variable
	const aiScene *scene;
	///std::vector of Mesh variables
	std::vector<Mesh> m_meshes;
	///std::string variable for a file path
	std::string m_path;
	///std::map with std::string as keys and uint as values
	std::map<std::string, uint> m_bone_mapping;
	///unit varialbe for number of bones
	uint m_num_bones = 0;
	///std::vector of BoneMatrix variables
	std::vector<BoneMatrix> m_bone_matrices;
	///aiMatrix4x4 variable
	aiMatrix4x4 m_global_inverse_transform;
	///GLuint variable for bone locations
	GLuint m_bone_location[MAX_BONES];
	///float variable for ticks per second
	float ticks_per_second = 0.0f;
	///bool variable for checking if a model is animated
	bool animated;

	/**
	* @brief  Processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	*
	* @param aiNode* node, const aiScene* scene
	*/
	void processNode(aiNode* node, const aiScene* scene);

	/**
	* @brief process mesh data
	*
	* @param aiNode* node, const aiScene* scene
	* @return Mesh
	*/
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);

	/**
	* @brief load material textures
	*
	* @param aiMaterial *mat, aiTextureType type, string typeName
	* @return vector<texture>
	*/
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

	/**
	* @brief finds position of a node
	*
	* @param float, const aiNodeAnim*
	* @return uint
	*/
	uint findPosition(float p_animation_time, const aiNodeAnim* p_node_anim);

	/**
	* @brief finds rotation of a node
	*
	* @param float, const aiNodeAnim*
	* @return uint
	*/
	uint findRotation(float p_animation_time, const aiNodeAnim* p_node_anim);

	/**
	* @brief finds scaling of a node
	*
	* @param float, const aiNodeAnim*
	* @return uint
	*/
	uint findScaling(float p_animation_time, const aiNodeAnim* p_node_anim);

	/**
	* @brief finds animation of a node
	*
	* @param const aiAnimation*, const std::string
	* @return const aiNodeAnim*
	*/
	const aiNodeAnim* findNodeAnim(const aiAnimation * p_animation, const std::string p_node_name);

	/**
	* @brief calculates interpolated scaling of a node
	*
	* @param float, const aiNodeAnim*
	* @return aiVector3D
	*/
	aiVector3D calcInterpolatedScaling(float p_animation_time, const aiNodeAnim* p_node_anim);

	/**
	* @brief calculates interpolated rotation of a node
	*
	* @param float, const aiNodeAnim*
	* @return aiQuaternion
	*/
	aiQuaternion calcInterpolatedRotation(float p_animation_time, const aiNodeAnim* p_node_anim);

	/**
	* @brief calculates interpolated position of a node
	*
	* @param float, const aiNodeAnim*
	* @return aiVector3D
	*/
	aiVector3D calcInterpolatedPosition(float p_animation_time, const aiNodeAnim* p_node_anim);

	/**
	* @brief transforms bones
	*
	* @param double, std::vector<aiMatrix4x4>&
	* @return
	*/
	void boneTransform(double time_in_sec, std::vector<aiMatrix4x4>& transforms);

	/**
	* @brief reads hierarchy of nodes
	*
	* @param float, const aiNode*, const aiMatrix4x4
	* @return void
	*/
	void readNodeHierarchy(float p_animation_time, const aiNode* p_node, const aiMatrix4x4 parent_transform);

	///glm::quat variable 
	glm::quat rotate_head_xz = glm::quat(cos(glm::radians(0.0f)), sin(glm::radians(0.0f)) * glm::vec3(1.0f, 0.0f, 0.0f));

	///std::vector of aiNode* variables
	std::vector<aiNode*> ai_nodes;
	
	///std::vector of aiNodeAnim* variables
	std::vector<aiNodeAnim*> ai_nodes_anim;

	/**
	* @brief recursively adds nodes to ai_nodes vector
	*
	* @param aiNode*
	* @return void
	*/
	void recursiveNodeProcess(aiNode* node);
	
	/*  Model Data  */

	///std::string variable for model directory
	std::string m_directory;
	///std::vector of Texture variables
	std::vector<Texture> m_textures_loaded;	
	///aiNode* varaible for root node
	aiNode* m_RootNode;
	///glm::mat4 variable for gloabal inverse transform
	glm::mat4 globalInverseTransform;


};