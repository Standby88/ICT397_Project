#include "Shader.h"
#include <GL\glew.h>

//Shader::Shader(const GLchar *vertexPath, const GLchar *fragPath)
Shader::Shader(const char *vertexPath, const char *fragPath)
{

	std::string vertexCode;
	std::string fragCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragPath);

		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragCode = fShaderStream.str();

	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE READ FAILURE" << std::endl;
	}

	const GLchar * vShaderCode = vertexCode.c_str();
	const GLchar * fShaderCode = fragCode.c_str();

	GLuint vertexShader, fragShader;
	GLint success;
	GLchar infolog[512];

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);

	//check for compile errors
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::VERTEX:COMPILATION FAILED\n" << infolog << std::endl;
	}

	//fragment shader
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fShaderCode, NULL);
	glCompileShader(fragShader);

	//check for compile errors
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::FRAGMENT:COMPILATION FAILED\n" << fragPath << " \n" << infolog << std::endl;
	}

	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertexShader);
	glAttachShader(this->Program, fragShader);
	glLinkProgram(this->Program);

	//check for linking errors
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->Program, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::PROGRAM:LINK FAILURE\n" << infolog << std::endl;
	}


	//can now free space from the shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}

void Shader::Use()
{
	glUseProgram(this->Program);
}

Shader::~Shader()
{
}
