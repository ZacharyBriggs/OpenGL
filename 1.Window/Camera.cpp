#include "Camera.h"
#include <glm/glm/gtc/matrix_transform.inl>
#include <glm/glm/gtc/constants.inl>
#include <iostream>


Camera::Camera()
{
	worldTransform = glm::mat4(1);
}


Camera::~Camera()
{
}

void Camera::update(float dt)
{
}

void Camera::setPerspective(float fov, float aspectRatio, float near, float far)
{
	projectionTransform = glm::perspective(fov, aspectRatio, near, far);
}

void Camera::setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{
	viewTransform = glm::lookAt(from, to, up);
}

void Camera::setPosition(glm::vec3 position)
{
	worldTransform[2].x += position[0];
	worldTransform[2].y += position[1];
	worldTransform[2].z += position[2];
	std::cout << worldTransform[2].x << " , "<< worldTransform[2].y << " , " << worldTransform[2].z << std::endl;
}

glm::mat4 Camera::getWorldTransform()
{
	return worldTransform;
}

glm::mat4 Camera::getView()
{
	return viewTransform;
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
	projectionViewTransform = viewTransform * projectionTransform;
}
