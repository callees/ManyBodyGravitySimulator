#pragma once
#include "glm/glm.hpp"

class Camera
{
public:
	Camera();
	Camera(glm::vec3 cameraStartingPosition);
	const glm::vec3 cameraRight_ = glm::vec3(1.0f, 0.0f, 0.0f);
	const glm::vec3 cameraUp_ = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 position();
	void setCameraMovespeed(float newMoveSpeed);
	void moveCameraUp();
	void moveCameraDown();
	void moveCameraLeft();
	void moveCameraRight();
	void moveCamera(glm::vec3 newCameraPosition);

private:
	float cameraMovespeed_;
	glm::vec3 cameraPosition_;
};

