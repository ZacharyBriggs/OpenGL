#pragma once
#include <glm/glm/glm.hpp>
#include "Camera.h"

struct GLFWwindow;

class FlyCamera : public Camera
{
public:
	FlyCamera();
	~FlyCamera();
	void update(GLFWwindow* window,float dt);
	void rotate(float radians, glm::vec3 axis);
	void setSpeed(float value);
private:
	float speed;
	glm::vec3 up;
};

