#define GLM_FORCE_SWIZZLE
#include <gl_core_4_4.h>
#include "MeshRenderer.h"

MeshRenderer::MeshRenderer()
{
}


MeshRenderer::~MeshRenderer()
{
}

int MeshRenderer::initialize(std::vector<unsigned int>& indices, std::vector<Vertex>& verticies)
{
	m_ibo = 0;
	m_vbo = 0;
	m_vao = 0;
	m_vertices = verticies;
	m_indices = indices;
	create_buffers();
	return 0;
}

int MeshRenderer::render()
{
	glBindVertexArray(m_vao);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLE_STRIP, m_indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	return 0;
}


int MeshRenderer::create_buffers()
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec4));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	

	return 0;
}
