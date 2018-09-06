#pragma once
#include "Vertex.h"
#include <vector>
#include "Application.h"

class RenderingGeometryApp : public Application
{
public:
	RenderingGeometryApp();
	~RenderingGeometryApp();
	std::vector<unsigned int> m_indices;
	std::vector<Vertex> m_vertices;
	unsigned int m_ibo;
	unsigned int m_vbo;
	unsigned int m_vao;
	unsigned int m_program;

	glm::mat4 m_model;
	glm::mat4 m_view;
	glm::mat4 m_projection;
	void startup() override;
	void update(float dt) override;
	void draw() override;
	void shutdown() override;	
	void create_buffers();
};

