#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ShaderProgram.h"
#include <vector>
#include "TwoVector.h"
#include "Camera.h"
#include "Body.h"

class NBodyRenderer
{
public:
	NBodyRenderer(std::string vertexShaderLocation, std::string fragmentShaderLocation, std::vector<std::vector<Body<TwoVector>>>* bodyHistory, GLFWwindow* window);
	NBodyRenderer(std::vector<std::vector<Body<TwoVector>>>* bodyHistory, GLFWwindow* window);
	void initialiseShaderProgram(std::string vertexShaderLocation, std::string fragmentShaderLocation);
	void setScaleFactor(float newScaleFactor);
	float getScaleFactor();
	void draw();


private:
	void drawBody(TwoVector bodyPosition);
	void getUniforms();
	void handleInputs();
	void handleCameraMovement();
	float calculateTimeBetweenFrames();

	GLFWwindow* window_;
	std::vector<std::vector<Body<TwoVector>>>* bodyHistory_ = nullptr;
	ShaderProgram nBodyShaderProgram_;
	Camera camera_;

	struct Matrix4Uniform
	{
		unsigned int uniformId;
		glm::mat4 matrix;
	};

	float scaleFactor_ = 0.001;
	float lastFrame_;
	float timeBetweenLastFrame_;

	int historyCounter_ = 0;

	Matrix4Uniform bodyPositionUniform_;
	Matrix4Uniform viewUniform_;
	Matrix4Uniform projectionUniform_;
	Matrix4Uniform resolutionUniform_;
	Matrix4Uniform translationUniform_;
	Matrix4Uniform massUniform_;
};

