#pragma once
#include "Application.h"
#include "Vertex.h"
#include <vector>

class RenderingGeometryApp : public Application
{
public:
	RenderingGeometryApp();
	~RenderingGeometryApp();
	std::vector<unsigned int> *m_indices;
	std::vector<Vertex> *m_Vertices;
	unsigned int m_ibo;
	unsigned int m_vbo;
	unsigned int m_vao;
	void startup() override;
};

