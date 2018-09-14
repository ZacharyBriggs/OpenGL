#include "GUIApplication.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/fwd.hpp"
#include "glm/glm/ext.hpp"
#include "imgui.h"
#include "gl_core_4_4.h"


void GUIApplication::startup()
{
	m_mesh = new MeshRenderer();
	m_defaultShader = new Shader();
	m_transform = new Transform();
	Vertex a = Vertex(glm::vec4(-10, 10, 0, 1), glm::vec4(1, 0, 0, 1));
	Vertex b = Vertex(glm::vec4(10, 10, 0, 1), glm::vec4(0, 1, 0, 1));
	Vertex c = Vertex(glm::vec4(10, -10, 0, 1), glm::vec4(0, 0, 1, 1));
	Vertex d = Vertex(glm::vec4(-10, -10, 0, 1), glm::vec4(0, 0, 0, 1));
	std::vector<Vertex> vertices = { a,b,c,d };
	std::vector<unsigned int> indices = { 0 ,1,2,2,3,0 };
	m_transform->SetModel(glm::mat4(1));
	m_mesh->initialize(indices, vertices);
	m_defaultShader->defaultLoad();
	m_defaultShader->attach();
}

void GUIApplication::shutdown()
{
}

void GUIApplication::update(float dt)
{
	glm::vec3 eye = glm::vec3(0, -10, -50);
	m_view = glm::lookAt(eye, m_transform->GetModel()[3].xyz(), glm::vec3(0, 1, 0));
	m_projection = glm::perspective(glm::quarter_pi<float>(), 800 / (float)600, 0.1f, 1000.f);
}

void GUIApplication::draw()
{
	if(ImGui::Button("Zoom In"))
	{
		glm::mat4 model = m_transform->GetModel();
		model[3].z -= 1;
		m_transform->SetModel(model);
	}
	if (ImGui::Button("Zoom Out"))
	{
		glm::mat4 model = m_transform->GetModel();
		model[3].z += 1;
		m_transform->SetModel(model);
	}
	m_defaultShader->bind();
	int handle = m_defaultShader->getUniform("ProjectionViewWorld");
	glm::mat4 mvp = m_projection * m_view*m_transform->GetModel();
	glUniformMatrix4fv(handle, 1, GL_FALSE, &mvp[0][0]);
	m_mesh->render();
	m_defaultShader->unbind();
}