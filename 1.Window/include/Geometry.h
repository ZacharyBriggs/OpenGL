#pragma once
#include "Vertex.h"
#include <vector>
class Geometry
{
public:
	Geometry();
	~Geometry();
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	std::vector<glm::vec4> genHalfCircle(int np, int radius);
	std::vector<glm::vec4> genSphere(std::vector<glm::vec4> points, unsigned int rm);
	std::vector<unsigned int> genSphereIndices(unsigned int np, unsigned int nm);
	std::vector<Vertex> genPlane(int size);
	std::vector<Vertex> genCube(std::vector<Vertex> vertices);
	std::vector<unsigned int> genCubeIndices();
};

