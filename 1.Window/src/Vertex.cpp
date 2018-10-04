#include "Vertex.h"



Vertex::Vertex()
{
}

Vertex::Vertex(glm::vec4 pos, glm::vec4 clr, glm::vec4 norm, glm::vec2 uv)
{
	position = pos;
	color = clr;
	normal = norm;
	UV = uv;
}


Vertex::~Vertex()
{
}


