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
	auto cosine = cos(radians);
	auto sine = sin(radians);
	auto newMat = glm::mat4(1);
	//if x rotate
	if (axis == glm::vec3(1, 0, 0))
	{
		//rotating along x means x doesn't change
		newMat[1].y = cosine;
		newMat[1].z = sine;
		newMat[2].y = -sin(radians);
		newMat[2].z = cosine;

	}
	//if y rotate
	if (axis == glm::vec3(0, 1, 0))
	{
		newMat[0].x = cosine;
		newMat[0].z = -sin(radians);
		newMat[2].x = sine;
		newMat[2].z = cosine;
	}
	//if z rotate
	if (axis == glm::vec3(0, 0, 1))
	{
		newMat[0].x = cosine;
		newMat[0].y = -sin(radians);
		newMat[1].x = sine;
		newMat[1].y = cosine;
	}
	viewTransform *= newMat;
}

void FlyCamera::setSpeed(float value)
{
	speed = value;
}
