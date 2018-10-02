#pragma once
#include "glm/glm/glm.hpp"

class Light
{
public:
	Light();
	~Light();
	glm::vec3 pos;
	glm::vec4 color;
	float intensity;
};

