#include "RenderingGeometryApp.h"
#include <gl_core_4_4.h>


RenderingGeometryApp::RenderingGeometryApp()
{
	m_Vertices = new std::vector<Vertex>;
}


RenderingGeometryApp::~RenderingGeometryApp()
{
}

void RenderingGeometryApp::startup()
{
	Vertex a(glm::vec4(-10,10,0,1));
	Vertex b(glm::vec4(10,10,0,1));
	Vertex c(glm::vec4(10,-10,0,1));
	Vertex d(glm::vec4(-10,-10,0,1));
	*m_Vertices = std::vector<Vertex>{ a, b, c, d };
	
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	*m_indices = std::vector<unsigned int>{ 0,1,2,2,3,0 };
	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * 32, m_Vertices, GL_STATIC_DRAW);
}
