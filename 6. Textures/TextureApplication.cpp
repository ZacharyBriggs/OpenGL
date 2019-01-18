#include "TextureApplication.h"
#define GLM_FORCE_SWIZZLE
#include "Shader.h"
#include "Geometry.h"
#include "MeshRenderer.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include <glm/glm/ext.hpp>
#include "imgui.h"
#include "gl_core_4_4.h"
#include <GLFW/glfw3.h>
#include <mutex>

float aC = 1;
float dC = 1;
float sC = 1;
float rt = 0;
double prevTime = glfwGetTime();
int nbFrames = 0;
glm::vec3 pos = glm::vec3(0);
TextureApplication::TextureApplication()
{
}

TextureApplication::~TextureApplication()
{
}

void FPMSCounter()
{
	double currentTime = glfwGetTime();
	nbFrames++;
	if (currentTime - prevTime >= 1.0)
	{
		
		ImGui::Text("%f ms / frame\n", 1000.0 / double(nbFrames));
		nbFrames = 0;
		prevTime += 1.0;
	}
}
void TextureApplication::startup()
{
	mesh = new MeshRenderer();
	defaultShader = new Shader();
	DaLight = new DirectionalLight();
	tex = new Texture("textures/moon.png");
	DaLight->color = glm::vec4(0, .5, 0, 1);
	DaLight->direction = glm::vec3(0, 1, 0);
	DaLight->pos = glm::vec3(0, -1, 0);
	defaultShader->load("shaders/texVert.vertex", 0);
	defaultShader->load("shaders/texFrag.fragment", 1);
	defaultShader->attach(); 

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	int nm = 21;
	int np = 20;
	pos = glm::vec3(0, 0, 0);
	std::vector<glm::vec4> points = Geometry::genHalfCircle(np, 5);
	std::vector<glm::vec4> spherePoints = Geometry::genSphere(points, nm, pos);
	indices = Geometry::genSphereIndices(np, nm);
	std::vector<glm::vec2> daUV;
	for (int x = 0; x <= nm; x++)
	{
		for (int y = 0; y < np; y++)
			daUV.push_back(glm::vec2((x / (float)np), y / ((float)nm - 1)));
	}
	for (int i = 0; i < spherePoints.size(); i++)
	{
		vertices.push_back(Vertex(spherePoints[i], glm::vec4(1, 1, 1, 1), daUV[i]));
	}
	static std::mutex Mutex;
	Mutex.lock();
	DaLight->pos = glm::vec3(pos.x, pos.y, pos.z);
	DaLight->direction = glm::vec3(0, -3, 0);
	Mutex.unlock();
	glm::vec4 material = vertices[0].color;
	vertices = Geometry::genPlane(10);
	indices = { 0,1,2,2,3,0 };
	mesh->initialize(indices, vertices);
}
void TextureApplication::shutdown()
{
}

void TextureApplication::update(float dt)
{
	ImGui::BeginChild("##scrolling");
	std::thread FPMSThread(FPMSCounter);
	ImGui::End();
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
	std::vector<glm::vec4> points3 = Geometry::genHalfCircle(np, 2);
	std::vector<glm::vec4> spherePoints3 = Geometry::genSphere(points3, nm, pos);
	std::vector<unsigned int> indices3 = Geometry::genSphereIndices(np, nm);
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
	static std::mutex Mutex;
	Mutex.lock();
	DaLight->pos = glm::vec3(pos.x, pos.y, pos.z);
	Mutex.unlock();
	glfwSetWindowUserPointer(m_window, this);
	glfwSetKeyCallback(m_window, key_callback);
	FPMSThread.join();
}

void TextureApplication::draw()
{
	defaultShader->bind();
	tex->bind(0);
	int handle = defaultShader->getUniform("ProjectionViewWorld");
	int textureHandle = defaultShader->getUniform("textureSampler");
	glm::mat4 mvp = m_projection * m_view * m_model;
	auto texPos = glm::vec2(0, 0);
	glUniform2fv(textureHandle,1,&texPos[0]);
	glUniformMatrix4fv(handle, 1, GL_FALSE, &mvp[0][0]);
	glm::vec3 col = DaLight->color;
	glm::vec3 view = glm::vec3(0, -10, 20);
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
