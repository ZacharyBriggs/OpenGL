#pragma once
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
	std::vector<glm::vec4> genHalfCircle(int numPoints, int radius);
	std::vector<glm::vec4> genSphere(std::vector<glm::vec4> points, int nm);
	std::vector<glm::vec4> rotatePoints(std::vector<glm::vec4> points, unsigned int rm);
};