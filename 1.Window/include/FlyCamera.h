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
	void setSpeed(float value);
private:
	float speed;
	glm::vec3 up;
};

