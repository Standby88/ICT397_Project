#pragma once

#include <map>
#include <iostream>
#include <string>
#include "GL\glew.h"


#include "SOIL2\SOIL2.h"


class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	bool AddTexture(const char * path);

	GLuint GetTexture(const char * path);

	static TextureManager & GetTextureManager();

	void DestroyTextureManager();

private:
	GLuint LoadTexture(const char * path);

	std::map <std::string, GLuint> textures;
};

