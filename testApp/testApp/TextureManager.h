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

	bool AddTexture(char * path);

	GLuint GetTexture(char * path);

private:
	GLuint LoadTexture(char * path);

	std::map <std::string, GLuint> textures;
};

