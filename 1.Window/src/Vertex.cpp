#include "Vertex.h"



Vertex::Vertex()
{
}

Vertex::Vertex(glm::vec4 pos, glm::vec4 clr, glm::vec2 uv)
{
	position = pos;
	color = clr;
	normal = glm::normalize(pos);
	UV = uv;
}


Vertex::~Vertex()
{
}


