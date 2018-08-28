#pragma once
#include <glm/glm/glm.hpp>

class FlyCamera
{
public:
	FlyCamera();
	~FlyCamera();
	void update(float dt);
	void setSpeed(float value);
private:
	float speed;
	glm::vec3 up;
};

