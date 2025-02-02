#include "NBodyRenderer.h"
#include "ShaderProgram.h"

#include "GL/glew.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



NBodyRenderer::NBodyRenderer(std::string vertexShaderLocation, std::string fragmentShaderLocation, std::vector<std::vector<Body<TwoVector>>>* bodyHistory, GLFWwindow* window) : bodyHistory_(bodyHistory), window_(window)
{
	initialiseShaderProgram(vertexShaderLocation, fragmentShaderLocation);
	getUniforms();
	glUniform2f(resolutionUniform_.uniformId, 1280.f, 720.0f);
}

NBodyRenderer::NBodyRenderer(std::vector<std::vector<Body<TwoVector>>>* bodyHistory, GLFWwindow* window) : NBodyRenderer("vertex.vert", "fragment.frag", bodyHistory, window)
{
}

void NBodyRenderer::initialiseShaderProgram(std::string vertexShaderLocation, std::string fragmentShaderLocation)
{
	nBodyShaderProgram_ = ShaderProgram(vertexShaderLocation, fragmentShaderLocation);
	nBodyShaderProgram_.initialise();
	nBodyShaderProgram_.use();
}


void NBodyRenderer::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	calculateTimeBetweenFrames();

	viewUniform_.matrix = glm::lookAt(camera_.position(), glm::vec3(camera_.position().x, camera_.position().y, 0.0f), camera_.cameraUp_);
	projectionUniform_.matrix = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
	translationUniform_.matrix = glm::scale(glm::mat4(1.0), glm::vec3(scaleFactor_));

	glUniformMatrix4fv(translationUniform_.uniformId, 1, GL_FALSE, glm::value_ptr(translationUniform_.matrix));
	glUniformMatrix4fv(viewUniform_.uniformId, 1, GL_FALSE, glm::value_ptr(viewUniform_.matrix));
	glUniformMatrix4fv(projectionUniform_.uniformId, 1, GL_FALSE, glm::value_ptr(projectionUniform_.matrix));
	auto currentHistory = bodyHistory_->at(historyCounter_);
	for (auto currentBody : currentHistory)
	{
		glUniform2f(bodyPositionUniform_.uniformId, currentBody.position().x1(), currentBody.position().x2());
		auto normalisedMass = currentBody.mass() / (5e29 + currentBody.mass());
		glUniform1f(massUniform_.uniformId, normalisedMass);
		glDrawArrays(GL_POINTS, 0, 1);
	}
	handleInputs();
	historyCounter_ += 100;
	if (historyCounter_ >= bodyHistory_->size())
		historyCounter_ = 0;
}


void NBodyRenderer::drawBody(TwoVector bodyPosition)
{
	glUniform2f(bodyPositionUniform_.uniformId, bodyPosition.x1(), bodyPosition.x2());
	glDrawArrays(GL_POINTS, 0, 1);
}

void NBodyRenderer::getUniforms()
{
	bodyPositionUniform_.uniformId = glGetUniformLocation(nBodyShaderProgram_.id(), "uniformBodyPosition");
	viewUniform_.uniformId = glGetUniformLocation(nBodyShaderProgram_.id(), "camera");
	projectionUniform_.uniformId = glGetUniformLocation(nBodyShaderProgram_.id(), "projection");
	resolutionUniform_.uniformId = glGetUniformLocation(nBodyShaderProgram_.id(), "iResolution");
	translationUniform_.uniformId = glGetUniformLocation(nBodyShaderProgram_.id(), "translation");
	massUniform_.uniformId = glGetUniformLocation(nBodyShaderProgram_.id(), "normalisedMass");
}

void NBodyRenderer::setScaleFactor(float newScaleFactor)
{
	scaleFactor_ = newScaleFactor;
}

float NBodyRenderer::getScaleFactor()
{
	return scaleFactor_;
}


void NBodyRenderer::handleInputs()
{
	handleCameraMovement();
}

void NBodyRenderer::handleCameraMovement()
{
	float cameraSpeed = 2.5f * timeBetweenLastFrame_ * (1 / scaleFactor_);
	camera_.setCameraMovespeed(cameraSpeed);
	if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS)
		camera_.moveCameraUp();
	if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS)
		camera_.moveCameraDown();
	if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS)
		camera_.moveCameraLeft();
	if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS)
		camera_.moveCameraRight();
}

float NBodyRenderer::calculateTimeBetweenFrames()
{
	float currentFrame = glfwGetTime();
	timeBetweenLastFrame_ = currentFrame - lastFrame_;
	lastFrame_ = currentFrame;

	return timeBetweenLastFrame_;
}