#pragma once
#include "Vertex.h"
#include <vector>

class MeshRenderer
{
public:
	MeshRenderer();
	~MeshRenderer();
	int initialize(std::vector<unsigned int>& indicies, std::vector<Vertex>& verticies);
	int render();
	int render(glm::mat4 m_projection, glm::mat4 m_view, glm::mat4 m_model);
	
private:
	std::vector<unsigned int> m_indices;
	std::vector<Vertex> m_vertices;
	unsigned int m_ibo;
	unsigned int m_vbo;
	unsigned int m_vao;
	int create_buffers();
};

