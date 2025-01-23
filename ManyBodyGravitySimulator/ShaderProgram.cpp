#include "ShaderProgram.h"
#include "Shader.h"
#include "GL/glew.h"

#include <iostream>


ShaderProgram::ShaderProgram()
{

}

ShaderProgram::ShaderProgram(std::string vertexShaderLocation, std::string fragmentShaderLocation)
{
	shaderProgramId_ = glCreateProgram();
	vertexShader_ = Shader(vertexShaderLocation, VERTEX_SHADER);
	fragmentShader_ = Shader(fragmentShaderLocation, FRAGMENT_SHADER);
}

void ShaderProgram::compileShaders()
{
	vertexShader_.compile();
	fragmentShader_.compile();
}

void ShaderProgram::attachShaders()
{
	glAttachShader(shaderProgramId_, vertexShader_.id());
	glAttachShader(shaderProgramId_, fragmentShader_.id());
	glLinkProgram(shaderProgramId_);
}

void ShaderProgram::deleteShaders()
{
	glDeleteShader(vertexShader_.id());
	glDeleteShader(fragmentShader_.id());
}

void ShaderProgram::checkLinkSuccess()
{
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgramId_, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgramId_, 512, NULL, infoLog);


		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	else {
		std::cout << "Shader program linked succesfully" << std::endl;
	}
}

void ShaderProgram::initialise()
{
	compileShaders();
	attachShaders();
	checkLinkSuccess();
	deleteShaders();

}

void ShaderProgram::use()
{
	glUseProgram(shaderProgramId_);
}

unsigned int ShaderProgram::id()
{
	return shaderProgramId_;
}
