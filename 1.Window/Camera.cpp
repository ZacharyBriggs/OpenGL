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
	worldTransform[3].x += position[0];
	worldTransform[3].y += position[1];
	worldTransform[3].z += position[2];
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
void Camera::setProjectionMatrix(glm::mat4 orthographic, float fieldOfView, float aspectRatio, float near, float far)
{
	orthographic[0].x = 1 / aspectRatio * tan(fieldOfView / 2);
	orthographic[1].y = 1 / tan(fieldOfView / 2);
	orthographic[2].z = -((far + near) / (far - near));
	orthographic[2].w = -1;
	orthographic[3].z = -(2 * (far*near) / (far - near));
}
