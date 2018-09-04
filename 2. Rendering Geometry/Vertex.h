#pragma once
#include "../dep/glm/glm/glm.hpp"

class Vertex
{
public:
	Vertex();
	Vertex(glm::vec4 pos);
	~Vertex();
	glm::vec4 position;
	glm::vec4 color;
};

