#define GLM_FORCE_SWIZZLE
#include "Shader.h"
#include "Geometry.h"
#include "MeshRenderer.h"
#include "DirectionalLight.h"
#include "LightingApplication.h"
#include <glm/glm/ext.hpp>
#include "gl_core_4_4.h"

LightingApplication::LightingApplication()
{
}


LightingApplication::~LightingApplication()
{
}

void LightingApplication::startup()
{
	mesh = new MeshRenderer();
	defaultShader = new Shader();
	geo = new Geometry();
	DaLight = new DirectionalLight();
	DaLight->color = glm::vec4(0, .5, 0, 1);
	DaLight->direction = glm::vec3(1, 1, 0);
	defaultShader->load("d.vertex", 0);
	defaultShader->load("b.fragment", 1);
	defaultShader->attach();

	/*std::vector<Vertex> vertices = genPlane(5);
	std::vector<unsigned int> indices = {0,1,2,3,0};*/

	//gen sphere
	int nm = 51;
	int np = 50;
	std::vector<glm::vec4> points = geo->genHalfCircle(np, 5);
	std::vector<glm::vec4> spherePoints = geo->genSphere(points, nm);
	std::vector<unsigned int> indices = geo->genSphereIndices(np, nm);
	std::vector<Vertex> vertices;
	for (glm::vec4 point : spherePoints)
	{
		vertices.push_back(Vertex(point, glm::vec4(1, 1, 1, 1)));
	}
	glm::vec4 material = vertices[0].color;
	mesh->initialize(indices, vertices);
}
float rt = 0;

void LightingApplication::update(float dt)
{
	rt += dt;
	glm::mat4 trans;
	float angle = glm::cos(rt*0.5f) * dt;
	glm::mat4 rot = glm::rotate(glm::mat4(1), glm::cos(dt), glm::vec3(0, 1, 0));
	trans = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));
	m_view = glm::lookAt(glm::vec3(0, -10, 20), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	m_projection = glm::perspective(glm::quarter_pi<float>(), 800 / (float)600, 0.1f, 1000.f);
	m_model = glm::mat4(1) * rot;
	/*m_model = glm::mat4(1);*/

}
void LightingApplication::draw()
{
	defaultShader->bind();
	int handle = defaultShader->getUniform("ProjectionViewWorld");
	int lightColorHandle = defaultShader->getUniform("lightColor");
	int lightPosHandle = defaultShader->getUniform("lightPos");
	int lightDirHandle = defaultShader->getUniform("lightDir");
	int CameraPosHandle = defaultShader->getUniform("cameraPos");
	glm::mat4 mvp = m_projection * m_view * m_model;
	glUniformMatrix4fv(handle, 1, GL_FALSE, &mvp[0][0]);
	glm::vec3 col = DaLight->color;
	glUniform3fv(lightColorHandle, 1, &col[0]);
	glUniform3fv(lightPosHandle, 1, &DaLight->pos[0]);
	glUniform3fv(lightDirHandle, 1, &DaLight->direction[0]);
	glm::vec3 view = glm::vec3(0, -10, 20);
	glUniform3fv(CameraPosHandle, 1, &view[0]);
	mesh->render();
	defaultShader->unbind();
}

void LightingApplication::shutdown()
{

}

