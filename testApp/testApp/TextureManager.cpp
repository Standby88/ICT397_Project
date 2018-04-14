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

bool TextureManager::AddTexture(const char *path)
{
	
	if (textures.count(path) != 1)
	{
		textures[path] = LoadTexture(path);
		return true;
	}
	return false;
}

GLuint TextureManager::GetTexture(const char *path)
{

	if(textures.count(path) == 1)
	{
		return textures[path];
	}

	return NULL;
}

GLuint TextureManager::LoadTexture(const char *path)
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

void TextureManager::DestroyTextureManager()
{
	TextureManager * texMan = &GetTextureManager();

	if (texMan != NULL)
		delete texMan;
}


TextureManager::~TextureManager()
{
}
