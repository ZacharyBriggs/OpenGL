  #include "Camera.h"
#include <glm/glm/gtc/matrix_transform.inl>
#include <glm/glm/gtc/constants.inl>
#include <iostream>
#include <assert.h>


Camera::Camera()
{
	projectionTransform = glm::mat4(1);
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
	std::cout << worldTransform[3].x << " , "<< worldTransform[3].y << " , " << worldTransform[3].z << std::endl;
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

void Camera::setProjection(glm::mat4 matrix)
{
	projectionTransform = matrix;
}

glm::mat4 Camera::getProjectionView()
{
	return projectionViewTransform;
}

void Camera::setOrthographicView(float right, float left, float top, float bottom, float far, float near)
{
	projectionTransform[0].x = 2 / (right - left);
	projectionTransform[1].y = 2 / (top - bottom);
	projectionTransform[2].z = -2 / (far - near);
	projectionTransform[3].x = -((right + left) / (right - left));
	projectionTransform[3].y = -((top + bottom) / (top - bottom));
	projectionTransform[3].z = -((far + near) / (far - near));
}

void Camera::updateProjectionViewTransform()
{
	projectionViewTransform =  projectionTransform * viewTransform;
}
void Camera::setPerspectiveView(float fov, float aspectRatio, float near, float far)
{
	projectionTransform[0].x = 1 / (aspectRatio * tan(fov / 2));
	projectionTransform[1].y = 1 / tan(fov / 2);
	projectionTransform[2].z = -((far + near) / (far - near));
	projectionTransform[2].w = -1;
	projectionTransform[3].z = -((2 *far*near) / (far - near));
}
