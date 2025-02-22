#pragma once
#include <string>

enum ShaderType {
	VERTEX_SHADER,
	FRAGMENT_SHADER
};

class Shader
{
public:
	Shader();
	Shader(std::string shaderPath, ShaderType shaderType);
	void compile();
	unsigned int id();
private:
	std::string shaderCode_;
	ShaderType shaderType_;
	unsigned int shaderId_;
};

