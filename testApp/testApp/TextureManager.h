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

	bool AddTexture(const std::string path);

	GLuint GetTexture(const std::string path);

	static TextureManager & GetTextureManager();

	void DestroyTextureManager();

private:
	GLuint LoadTexture(const std::string path);

	std::map <std::string, GLuint> textures;
};

