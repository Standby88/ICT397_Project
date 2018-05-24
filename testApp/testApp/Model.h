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
	*/
	Model(std::string path);
	~Model() {};

	static const uint MAX_BONES = 100;
	
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
	*@param string path
	*/
	void loadModel(string path);
	
	
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

	Assimp::Importer importer;
	const aiScene *scene;
	vector<Mesh> m_meshes;
	std::string m_path;
	
	std::map<std::string, uint> m_bone_mapping;
	uint m_num_bones = 0;
	std::vector<BoneMatrix> m_bone_matrices;
	aiMatrix4x4 m_global_inverse_transform;

	GLuint m_bone_location[MAX_BONES];
	float ticks_per_second = 0.0f;

	bool animated;
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

	uint findPosition(float p_animation_time, const aiNodeAnim* p_node_anim);
	uint findRotation(float p_animation_time, const aiNodeAnim* p_node_anim);
	uint findScaling(float p_animation_time, const aiNodeAnim* p_node_anim);
	const aiNodeAnim* findNodeAnim(const aiAnimation * p_animation, const string p_node_name);

	aiVector3D calcInterpolatedScaling(float p_animation_time, const aiNodeAnim* p_node_anim);
	aiQuaternion calcInterpolatedRotation(float p_animation_time, const aiNodeAnim* p_node_anim);
	aiVector3D Model::calcInterpolatedPosition(float p_animation_time, const aiNodeAnim* p_node_anim);

	void boneTransform(double time_in_sec, vector<aiMatrix4x4>& transforms);
	void readNodeHierarchy(float p_animation_time, const aiNode* p_node, const aiMatrix4x4 parent_transform);

	glm::quat rotate_head_xz = glm::quat(cos(glm::radians(0.0f)), sin(glm::radians(0.0f)) * glm::vec3(1.0f, 0.0f, 0.0f));

	std::vector<aiNode*> ai_nodes;
	
	std::vector<aiNodeAnim*> ai_nodes_anim;
	void recursiveNodeProcess(aiNode* node);
	
	/*  Model Data  */

	string m_directory;
	vector<Texture> m_textures_loaded;	
	aiNode* m_RootNode;
	glm::mat4 globalInverseTransform;


};