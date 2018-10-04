#include "FlyCamera.h"
#include <glfw\glfw3.h>


FlyCamera::FlyCamera()
{
	speed = 1;
}


FlyCamera::~FlyCamera()
{
}

void FlyCamera::update(GLFWwindow* window,float dt)
{
	if(glfwGetKey(window,GLFW_KEY_W))
	{
		Camera::setPosition(glm::vec3(0, -speed*dt, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		Camera::setPosition(glm::vec3(speed*dt, 0, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		Camera::setPosition(glm::vec3(0, speed * dt, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		Camera::setPosition(glm::vec3(-speed*dt, 0, 0));
	}
}

void FlyCamera::setSpeed(float value)
{
	speed = value;
}
