#define GLM_FORCE_SWIZZLE
#include "MeshRenderer.h"
#include "Vertex.h"
#include <vector>
#include "Application.h"
#include "Shader.h"
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
	defaultShader = new Shader();
	Vertex a = Vertex(glm::vec4(-10, 10, 0, 1), glm::vec4(1, 0, 0, 1));
	Vertex b = Vertex(glm::vec4(10, 10, 0, 1), glm::vec4(0, 1, 0, 1));
	Vertex c = Vertex(glm::vec4(10, -10, 0, 1), glm::vec4(0, 0, 1, 1));
	Vertex d = Vertex(glm::vec4(-10, -10, 0, 1), glm::vec4(0, 0, 0, 1));
	std::vector<Vertex> vertices = { a,b,c,d };
	std::vector<unsigned int> indices = { 0 ,1,2,2,3,0 };
	mesh->initialize(indices, vertices);
	defaultShader->defaultLoad();
	defaultShader->attach();
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
	defaultShader->bind();
	int handle = defaultShader->getUniform("ProjectionViewWorld");
	glm::mat4 mvp = m_projection*m_view*m_model;
	glUniformMatrix4fv(handle, 1, GL_FALSE, &mvp[0][0]);
	mesh->render();
	defaultShader->unbind();
}

void RenderingGeometryApp::shutdown()
{
}

