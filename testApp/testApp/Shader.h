#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
extern "C"
{
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include <LuaBridge.h>
#include <string>
#include <glm\glm.hpp>
//#include <GL\glew.h>

class Shader
{
public:

	//Shader(const GLchar *vertexPath, const GLchar *fragPath);
	Shader(const char *vertexPath, const char *fragPath);
	void Use();
	~Shader();
	static void scriptRegister(lua_State * L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginNamespace("Shader")
			.beginClass<Shader>("Shader")
			.addConstructor<void(*)(const char*, const char*)>()
			.endClass()
			.endNamespace();
	}

	int Program;
	//GLuint Program;
};

