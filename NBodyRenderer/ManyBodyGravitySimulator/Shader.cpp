#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <GL/glew.h>

Shader::Shader()
{
}

Shader::Shader(std::string shaderPath, ShaderType shaderType) : shaderType_(shaderType)
{

	if (shaderType_ == VERTEX_SHADER)
	{
		shaderId_ = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (shaderType_ == FRAGMENT_SHADER)
	{
		shaderId_ = glCreateShader(GL_FRAGMENT_SHADER);
	}

	std::string shaderCode;
	std::ifstream vShaderFile;
	// ensure ifstream objects can throw exceptions:
	try
	{
		// open files
		vShaderFile.open(shaderPath);
		std::stringstream vShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		// convert stream into string
		shaderCode = vShaderStream.str();
		shaderCode_ = shaderCode;
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
}

void Shader::compile()
{
	const char* shaderCodePointer = shaderCode_.c_str();
	glShaderSource(shaderId_, 1, &shaderCodePointer, NULL);
	glCompileShader(shaderId_);
}

unsigned int Shader::id()
{
	return shaderId_;
}
