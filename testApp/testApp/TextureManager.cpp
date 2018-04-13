#include "TextureManager.h"



TextureManager::TextureManager()
{
}

bool TextureManager::AddTexture(char *path)
{
	
	if (textures.count(path))
	{
		textures[path] = LoadTexture(path);
		return true;
	}
	return false;
}

GLuint TextureManager::GetTexture(char *path)
{
	std::map <std::string, GLuint>::iterator it = textures.find(path);

	if(it != textures.end())
	{
		//std::cout << "Model at ";
		//std::cout << models[modelPath]->getName() << endl;
		return textures[path];
	}

	return NULL;
}

GLuint TextureManager::LoadTexture(char *path)
{
	//Generate texture ID and load texture data
	GLuint textureID;
	glGenTextures(1, &textureID);

	int imageWidth, imageHeight;

	unsigned char *image = SOIL_load_image(path, &imageWidth, &imageHeight, 0, SOIL_LOAD_RGB);

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


TextureManager::~TextureManager()
{
}
