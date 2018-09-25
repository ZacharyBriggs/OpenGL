#pragma once
#include "Vertex.h"
#include "Application.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/fwd.hpp"
#include <vector>

class MeshRenderer;
class Shader;

class RenderingGeometryApp : public Application
{
public:
	MeshRenderer* mesh;
	Shader* defaultShader;
	RenderingGeometryApp();
	~RenderingGeometryApp();
	unsigned int m_program;
	glm::mat4 m_model;
	glm::mat4 m_view;
	glm::mat4 m_projection;
	void startup() override;
	void update(float dt) override;
	void draw() override;
	void shutdown() override;
	std::vector<glm::vec4> genHalfCircle(int np, int radius);
	std::vector<glm::vec4> genSphere(std::vector<glm::vec4> points, unsigned int rm);
	std::vector<Vertex> genCube(std::vector<Vertex> vertices);
	std::vector<Vertex> genPlane(int size);
	std::vector<unsigned int> genIndices(unsigned int np,unsigned int nm);
	std::vector<unsigned int> genCubeIndices();
};