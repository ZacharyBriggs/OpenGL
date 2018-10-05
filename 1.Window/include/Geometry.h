#pragma once
#include "Vertex.h"
#include <vector>
class Geometry
{
public:
	Geometry();
	~Geometry();
	static std::vector<glm::vec4> genHalfCircle(int np, int radius);
	static std::vector<glm::vec4> genSphere(std::vector<glm::vec4> points, unsigned int rm, glm::vec3 position);
	static std::vector<unsigned int> genSphereIndices(unsigned int np, unsigned int nm);
	static std::vector<Vertex> genPlane(int size);
	static std::vector<Vertex> genCube(std::vector<Vertex> vertices);
	static std::vector<unsigned int> genCubeIndices();
};

