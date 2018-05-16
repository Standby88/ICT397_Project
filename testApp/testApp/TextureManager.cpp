#include "TextureManager.h"



TextureManager::TextureManager()
{
}

TextureManager & TextureManager::GetTextureManager()
{
	static TextureManager * texMan = NULL;

	if (texMan == NULL)
	{
		texMan = new TextureManager();

	}

	return * texMan;
}

bool TextureManager::AddTexture(const std::string path)
{
	
	if (textures.count(path) != 1)
	{
		textures[path] = LoadTexture(path);
		return true;
	}
	return false;
}

GLuint TextureManager::GetTexture(const std::string path)
{

	if(textures.count(path) == 1)
	{
		return textures[path];
	}
	std::cout << "no texture";
	return NULL;
}

GLuint TextureManager::LoadTexture(const std::string path)
{
	//Generate texture ID and load texture data
	GLuint textureID;
	glGenTextures(1, &textureID);
	const char* Cpath = path.c_str();
	int imageWidth, imageHeight;

	unsigned char *image = SOIL_load_image(Cpath, &imageWidth, &imageHeight, 0, SOIL_LOAD_RGB);

	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
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

void TextureManager::DestroyTextureManager()
{
	TextureManager * texMan = &GetTextureManager();

	if (texMan != NULL)
		delete texMan;
}

//Skybox is loaded and stored differently than normal images
//the vector of imagepaths needs to be in order
//right, left, top, bottom, back, front
GLuint TextureManager::LoadSkyboxCubeMap(std::vector<std::string> faces)
{
	GLuint textureID;
	glGenTextures(1, &textureID);

	int imageWidth, imageHeight;
	unsigned char *image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	for (GLuint i = 0; i < faces.size(); i++)
	{
		image = SOIL_load_image(faces[i].c_str(), &imageWidth, &imageHeight, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}

GLuint TextureManager::GetSkyboxCubeMap()
{
	return skybox;
}



TextureManager::~TextureManager()
{
}
