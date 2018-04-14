#pragma once
#include "GameObject.h"
#include <vector>
#include "RAwIMGLoader.h"
#include "Mesh.h"
#include "SOIL2/SOIL2.h"
struct VertexRGB
{
	float t[6];
};
/**
* @class WorldTerrain
* @brief used to represent terrain of the world
*
*
* @author 
* @version 1
* @date
*
* @todo
*
* @bug
*/
class WorldTerrain : public GameObject
{
private:

	Mesh terMesh;
	///temp test string
	unsigned char *terrainData;
	glm::vec3 scale;

	int size;

	bool inbounds(int xpos, int zpos);
	unsigned char getHeightColor(int xpos, int zpos);
	float getHeight(int xpos, int zpos);
public:

	/**
	* @brief World terrain constructor
	*
	*/
	WorldTerrain();
	
	/**
	* @brief destructor for worldterrain object
	*/
	~WorldTerrain();

	/**
	* @brief render the terrain
	*/
	void Draw(Shader);

	/**
	* @brief register all functions to lua to be used.
	*
	* @param lua_State * L
	*/
	static void scriptRegister(lua_State * L);
	
	void collectData();
	GLint TextureFromFile(const char *path, string directory)
	{
		//Generate texture ID and load texture data
		string filename = string(path);
		filename = directory + '/' + filename;
		GLuint textureID;
		glGenTextures(1, &textureID);

		int width, height;

		unsigned char *image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

		// Assign texture to ID
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		// Parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		SOIL_free_image_data(image);

		return textureID;
	}
	bool loadHeightfield(char *filename, const int size);

	void setScalingFactor(glm::vec3 newScale);


	int getSize();
};

