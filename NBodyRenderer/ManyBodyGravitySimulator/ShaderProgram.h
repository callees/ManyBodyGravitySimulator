#pragma once
#include "Shader.h"
class ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(std::string vertexShaderLocation, std::string fragmentShaderLocation);
	void initialise();
	void use();
	unsigned int id();
private:
	void compileShaders();
	void attachShaders();
	void deleteShaders();

	void checkLinkSuccess();
	Shader vertexShader_;
	Shader fragmentShader_;
	unsigned int shaderProgramId_;
};

