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
	//from is the camera's position
	//to is what you want the camera to look at
	//up is which the direction the camera will consider above it
	//the view matrix looks like 
	//   right.x,   right.y,   right.z, 0	X-Axis
	//      up.x,      up.y,      up.z, 0	Y-Axis
	// forward.x, forward.y, forward.z, 0	Z-Axis
	//    from.x,    from.y,    from.z, 1	 

	//forward is the direcion from the camera to the position we're looking at
	glm::vec3 forward = glm::normalize(to - from);	
	//since we know the other 2 axes we can get the third with cross product
	glm::vec3 right = glm::normalize(glm::cross(up, forward));
	//We give up as an argument in the function
	glm::vec3 upNormal = glm::normalize(glm::cross(forward, right));

	glm::mat4 V = glm::mat4(
		right.x,	right.y,	right.z,	0, 
		upNormal.x,	upNormal.y,	upNormal.z, 0, 
		forward.x,	forward.y,	forward.z,	0, 
		0,			0,			0,			1);
	glm::mat4 T = glm::mat4(
		glm::vec4(1, 0, 0, 0), 
		glm::vec4(0, 1, 0, 0), 
		glm::vec4(0, 0, 1, 0), 
		glm::vec4(from   , 1));
	
	viewTransform = V*T;
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
