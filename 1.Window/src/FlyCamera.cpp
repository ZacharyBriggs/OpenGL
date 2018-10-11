#include "FlyCamera.h"
#include <glfw\glfw3.h>


FlyCamera::FlyCamera()
{
	speed = 0.25;
}


FlyCamera::~FlyCamera()
{
}

void FlyCamera::update(GLFWwindow* window,float dt)
{
	if(glfwGetKey(window,GLFW_KEY_W))
	{
		Camera::setPosition(glm::vec3(0, -speed, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		Camera::setPosition(glm::vec3(-speed, 0, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		Camera::setPosition(glm::vec3(0, speed, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		Camera::setPosition(glm::vec3(speed, 0, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT))
	{
		rotate(.10, glm::vec3(0, 1, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT))
	{
		rotate(-0.10, glm::vec3(0, 1, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_UP))
	{
		rotate(.10, glm::vec3(1, 0, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN))
	{
		rotate(-0.10, glm::vec3(1, 0, 0));
	}
}

void FlyCamera::rotate(float radians, glm::vec3 axis)
{
	auto cos = glm::cos(radians);
	auto sin = glm::sin(radians);
	glm::vec3 x_Axis = glm::vec3(1, 0, 0);
	glm::vec3 y_Axis = glm::vec3(0, 1, 0);
	glm::vec3 z_Axis = glm::vec3(0, 0, 1);
	//X rotation
	if (axis == x_Axis)
	{
		y_Axis = glm::vec3(0, cos, sin);
		z_Axis = glm::vec3(0, -sin, cos);
	}
	//Y rotation
	else if (axis == y_Axis)
	{
		x_Axis = glm::vec3(cos, 0, -sin);
		z_Axis = glm::vec3(sin, 0, cos);
	}
	//Z rotation
	else if (axis == z_Axis)
	{
		x_Axis = glm::vec3(cos, sin, 0);
		y_Axis = glm::vec3(-sin, cos, 0);
	}
	auto rotation = glm::mat4(
		x_Axis.x, y_Axis.x, z_Axis.x, 0,
		x_Axis.y, y_Axis.y, z_Axis.y, 0,
		x_Axis.z, y_Axis.z, z_Axis.z, 0,
		0, 0, 0, 1
	);
	viewTransform *= rotation;
}

void FlyCamera::setSpeed(float value)
{
	speed = value;
}
