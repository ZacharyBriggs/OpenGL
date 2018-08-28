#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::update(float dt)
{
}

void Camera::setPerspective(float fov, float aspectRatio, float, float)
{
}

void Camera::setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{
}

void Camera::setPosition(glm::vec3 position)
{
}

glm::mat4 Camera::getWorldTransform()
{
	return glm::mat4();
}

glm::mat4 Camera::getView()
{
	return glm::mat4();
}

glm::mat4 Camera::getProjection()
{
	return projectionTransform;
}

glm::mat4 Camera::getProjectionView()
{
	return projectionViewTransform;
}

void Camera::updateProjectionViewTransform()
{
}
