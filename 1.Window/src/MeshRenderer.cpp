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
	//We set m_vertices and m_indices to the values passed in call create buffers 
	//and make sure ibo,vbo,and vao aren’t null.
	m_ibo = 0;
	m_vbo = 0;
	m_vao = 0;
	m_nbo = 0;
	m_ubo = 0;
	m_vertices = verticies;
	m_indices = indices;
	create_buffers();
	return 0;
}

int MeshRenderer::render()
{
	glBindVertexArray(m_vao);
	glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLE_STRIP);
	glPrimitiveRestartIndex(0xFFFF);
	glEnable(GL_PRIMITIVE_RESTART);
	glDrawElements(GL_TRIANGLE_STRIP, m_indices.size(), GL_UNSIGNED_INT, 0);
	glDisable(GL_PRIMITIVE_RESTART);
	glBindVertexArray(0);
	return 0;
}


int MeshRenderer::create_buffers()
{
	//Generate vao,vbo, and ibo.
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);
	glGenBuffers(1, &m_nbo);
	glGenBuffers(1, &m_ubo);

	//Bind vao to the vertex array and then give it the vertices of the geometry to render
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

	//Bind ibo to the array buffer and give it the indices of the geometry we want to render
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);;

	//Enable a pointer for the position
	//the arguments are the following: Where the variable is in the AttribArray, the number of values of the variable, 
	//the type of the values in the variable, if they values are normalized, the size of the class the variable is in, 
	//and how many bytes the variable is from the start of the AttribArray
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	//Enable a pointer for the color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec4));

	//Enable a pointer for the normal
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(sizeof(glm::vec4)*2));

	//Enable a pointer for the UV
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(sizeof(glm::vec4)*3));

	//Unbind everything that was bound
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return 0;
}
