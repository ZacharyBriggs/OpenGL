#define GLM_FORCE_SWIZZLE

#include "RenderingGeometryApp.h"


RenderingGeometryApp::RenderingGeometryApp()
{
}


RenderingGeometryApp::~RenderingGeometryApp()
{
}

void RenderingGeometryApp::startup()
{
	mesh = new MeshRenderer();
	Vertex a = Vertex(glm::vec4(-10, 10, 0, 1), glm::vec4(1, 0, 0, 1));
	Vertex b = Vertex(glm::vec4(10, 10, 0, 1), glm::vec4(0, 1, 0, 1));
	Vertex c = Vertex(glm::vec4(10, -10, 0, 1), glm::vec4(0, 0, 1, 1));
	Vertex d = Vertex(glm::vec4(-10, -10, 0, 1), glm::vec4(0, 0, 0, 1));
	std::vector<Vertex> vertices = { a,b,c,d };
	std::vector<unsigned int> indices = { 0 ,1,2,2,3,0 };
	mesh->initialize(indices, vertices);
}

void RenderingGeometryApp::update(float dt)
{
	m_model = glm::mat4(1);
	glm::vec3 eye = glm::vec3(0, -10, -50);
	m_view = glm::lookAt(eye, m_model[3].xyz(), glm::vec3(0, 1, 0));
	m_projection = glm::perspective(glm::quarter_pi<float>(), 800 / (float)600, 0.1f, 1000.f);

}
void RenderingGeometryApp::draw()
{
	mesh->render(m_projection, m_view, m_model);
	mesh->render(m_projection, m_view, m_model*glm::translate(m_model, glm::vec3(5, 0, 0)));
	mesh->render(m_projection, m_view, m_model*glm::translate(m_model, glm::vec3(-5, 0, 0)));
}

void RenderingGeometryApp::shutdown()
{
}

