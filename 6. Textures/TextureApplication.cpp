#include "TextureApplication.h"
#define GLM_FORCE_SWIZZLE
#include "Shader.h"
#include "Geometry.h"
#include "MeshRenderer.h"
#include "DirectionalLight.h"
#include <glm/glm/ext.hpp>
#include "gl_core_4_4.h"
#include <GLFW/glfw3.h>

float aC = 1;
float dC = 1;
float sC = 1;
float rt = 0;
glm::vec3 pos = glm::vec3(0);
TextureApplication::TextureApplication()
{
}

TextureApplication::~TextureApplication()
{
}

void TextureApplication::startup()
{
	mesh = new MeshRenderer();
	defaultShader = new Shader();
	DaLight = new DirectionalLight();
	DaLight->color = glm::vec4(0, .5, 0, 1);
	DaLight->direction = glm::vec3(0, 1, 0);
	DaLight->pos = glm::vec3(0, -1, 0);
	defaultShader->load("d.vertex", 0);
	defaultShader->load("b.fragment", 1);
	defaultShader->attach();

	int nm = 11;
	int np = 10;
	pos = glm::vec3(-7, 0, 0);
	std::vector<glm::vec4> points = geo->genHalfCircle(np, 5);
	std::vector<glm::vec4> spherePoints = geo->genSphere(points, nm, pos);
	std::vector<unsigned int> indices = geo->genSphereIndices(np, nm);
	std::vector<Vertex> vertices;
	std::vector<glm::vec2> daUV;
	float V = 0;
	for (int i = 0; i<2; i++)
	{
		for (int j = 0; j < spherePoints.size() / 2; j++)
		{
			daUV.push_back(glm::vec2((float)j / (spherePoints.size() / 2), V));
		}
		V++;
	}
	for (int i = 0; i < spherePoints.size(); i++)
	{
		vertices.push_back(Vertex(spherePoints[i], glm::vec4(1, 1, 1, 1), daUV[i]));
	}
	DaLight->pos = glm::vec3(pos.x, pos.y, pos.z);
	DaLight->direction = glm::vec3(0, -3, 0);
	glm::vec4 material = vertices[0].color;
	mesh->initialize(indices, vertices);
}

void TextureApplication::shutdown()
{
}

void TextureApplication::update(float dt)
{
	rt += dt;
	glm::mat4 trans;
	float angle = glm::cos(rt*0.5f) * dt;
	glm::mat4 rot = glm::rotate(glm::mat4(1), glm::cos(dt), glm::vec3(0, 1, 0));
	trans = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));
	m_view = glm::lookAt(glm::vec3(0, -10, 20), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	m_projection = glm::perspective(glm::quarter_pi<float>(), 800 / (float)600, 0.1f, 1000.f);
	m_model = glm::mat4(1) * rot;
	m_model = glm::mat4(1);
	int nm = 12;
	int np = 11;
	std::vector<glm::vec4> points3 = geo->genHalfCircle(np, 2);
	std::vector<glm::vec4> spherePoints3 = geo->genSphere(points3, nm, pos);
	std::vector<unsigned int> indices3 = geo->genSphereIndices(np, nm);
	std::vector<Vertex> vertices3;
	for (glm::vec4 point : spherePoints3)
	{
		vertices3.push_back(Vertex(point, glm::vec4(1, 1, 1, 1), glm::vec2(0)));
	}

	if (glfwGetKey(m_window, GLFW_KEY_UP))
		pos.y += 0.1;
	if (glfwGetKey(m_window, GLFW_KEY_DOWN))
		pos.y -= 0.1;
	if (glfwGetKey(m_window, GLFW_KEY_RIGHT))
		pos.x += 0.1;
	if (glfwGetKey(m_window, GLFW_KEY_LEFT))
		pos.x -= 0.1;
	DaLight->pos = glm::vec3(pos.x, pos.y, pos.z);
	glfwSetWindowUserPointer(m_window, this);
	glfwSetKeyCallback(m_window, key_callback);

}

void TextureApplication::draw()
{
	defaultShader->bind();
	int handle = defaultShader->getUniform("ProjectionViewWorld");
	int lightColorHandle = defaultShader->getUniform("lightColor");
	int lightPosHandle = defaultShader->getUniform("lightPos");
	int lightDirHandle = defaultShader->getUniform("lightDir");
	int CameraPosHandle = defaultShader->getUniform("cameraPos");
	int ambientCoHandle = defaultShader->getUniform("ambientCo");
	int diffuseCoHandle = defaultShader->getUniform("diffuseCo");
	int specularCoHandle = defaultShader->getUniform("specularCo");
	glm::mat4 mvp = m_projection * m_view * m_model;

	glUniformMatrix4fv(handle, 1, GL_FALSE, &mvp[0][0]);
	glm::vec3 col = DaLight->color;
	glUniform3fv(lightColorHandle, 1, &col[0]);
	glUniform3fv(lightPosHandle, 1, &DaLight->pos[0]);
	glUniform3fv(lightDirHandle, 1, &DaLight->direction[0]);
	glm::vec3 view = glm::vec3(0, -10, 20);
	glUniform3fv(CameraPosHandle, 1, &view[0]);
	glUniform1fv(ambientCoHandle, 1, &aC);
	glUniform1fv(diffuseCoHandle, 1, &dC);
	glUniform1fv(specularCoHandle, 1, &sC);
	mesh->render();
	defaultShader->unbind();
}

void TextureApplication::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	TextureApplication* instance = (TextureApplication*)glfwGetWindowUserPointer(window);
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_1)
			aC == 1 ? aC = 0 : aC = 1;
		if (key == GLFW_KEY_2)
			dC == 1 ? dC = 0 : dC = 1;
		if (key == GLFW_KEY_3)
			sC == 1 ? sC = 0 : sC = 1;
	}
}