#define GLM_FORCE_SWIZZLE
#include <gl_core_4_4.h>
#include "MeshRenderer.h"
#include "RenderingGeometryApp.h"

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

int MeshRenderer::render(glm::mat4 m_projection,glm::mat4 m_view, glm::mat4 m_model)
{
	glBindVertexArray(m_vao);
	glUseProgram(m_program);
	int variableId = glGetUniformLocation(m_program, "ProjectionViewWorld");
	glm::mat4 mvp = m_projection * m_view * m_model;
	glUniformMatrix4fv(variableId, 1, GL_FALSE, &mvp[0][0]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLE_STRIP, m_indices.size(), GL_UNSIGNED_INT, 0);

	glUseProgram(0);
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

	const char*	vsSource = "#version 410\n \
                            layout(location = 0) in vec4 Position; \
                            layout(location = 1) in vec4 Color; \
                            out vec4 vColor; \
                            uniform mat4 ProjectionViewWorld; \
                            void main() { vColor = Color; \
                            gl_Position = ProjectionViewWorld * Position; }";

	const char *fsSource = "#version 410\n \
                            in vec4 vColor; \
                            out vec4 FragColor; \
                            void main() { FragColor = vColor; }";
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, (const char**)&vsSource, 0);
	glCompileShader(vertexShader);
	glShaderSource(fragmentShader, 1, (const char**)&fsSource, 0);
	glCompileShader(fragmentShader);
	m_program = glCreateProgram();
	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);
	return 0;
}