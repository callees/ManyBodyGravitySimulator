#include "Camera.h"

Camera::Camera()
{
	cameraPosition_ = glm::vec3(0.0f,0.0f,1.0f);
}

Camera::Camera(glm::vec3 cameraStartingPosition) : cameraPosition_(cameraStartingPosition)
{
}

void Camera::moveCamera(glm::vec3 directionToMove)
{
	cameraPosition_ += cameraMovespeed_*directionToMove;
}

glm::vec3 Camera::position()
{
	return cameraPosition_;
}

void Camera::setCameraMovespeed(float newMoveSpeed)
{
	cameraMovespeed_ = newMoveSpeed;
}

void Camera::moveCameraUp()
{
	moveCamera(cameraUp_);
}

void Camera::moveCameraDown()
{
	moveCamera(-cameraUp_);
}

void Camera::moveCameraLeft()
{
	moveCamera(-cameraRight_);
}

void Camera::moveCameraRight()
{
	moveCamera(cameraRight_);
}
