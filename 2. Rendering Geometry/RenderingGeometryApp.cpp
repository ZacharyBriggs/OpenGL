#define GLM_FORCE_SWIZZLE
#include "Shader.h"
#include "MeshRenderer.h"
#include "Vertex.h"
#include "RenderingGeometryApp.h"
#include <glm/glm/ext.hpp>
#include "gl_core_4_4.h"



RenderingGeometryApp::RenderingGeometryApp():m_model(glm::mat4(1))
{
}


RenderingGeometryApp::~RenderingGeometryApp()
{
}

void RenderingGeometryApp::startup()
{
	mesh = new MeshRenderer();
	defaultShader = new Shader();
	defaultShader->load("d.dik", 0);
	defaultShader->load("b.but", 1);
	defaultShader->attach();
	std::vector<glm::vec4> points = genHalfCircle(10, 10);
	points = rotatePoints(points, 10);

	std::vector<unsigned int> indices = genIndices(10,10);

	std::vector<Vertex> vertexs;
	for(glm::vec4 point : points)
	{
		vertexs.push_back(Vertex(point, glm::vec4(1, 1, 1, 1)));
	}
	mesh->initialize(indices, vertexs);
}
float rt = 0;

void RenderingGeometryApp::update(float dt)
{ 
	rt += dt;
	glm::mat4 rot;
	glm::mat4 trans;
	float angle = glm::cos(rt*0.5f) * dt;
	rot = glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0));
	trans = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));
	m_view = glm::lookAt(glm::vec3(0, -10, 40), glm::vec3(0,0,0), glm::vec3(0, 1, 0));
	m_projection = glm::perspective(glm::quarter_pi<float>(), 800 / (float)600, 0.1f, 1000.f);
	m_model = glm::mat4(1) * trans * rot;
}
void RenderingGeometryApp::draw()
{
	defaultShader->bind();
	int handle = defaultShader->getUniform("ProjectionViewWorld");
	 
	glm::mat4 mvp = m_projection * m_view * m_model;
	glUniformMatrix4fv(handle, 1, GL_FALSE, &mvp[0][0]);
	mesh->render();
	defaultShader->unbind();
}

void RenderingGeometryApp::shutdown()
{

}

std::vector<glm::vec4> RenderingGeometryApp::genHalfCircle(int numPoints,int radius)
{
	float angle = 3.14 / numPoints;
	std::vector<glm::vec4> points;
	for (float theta = 0; theta < 3.14; theta += angle)
	{
		points.push_back(glm::vec4(cos(theta)*radius, sin(theta)*radius, 0, 1));
	}
	return points;
}

std::vector<glm::vec4> RenderingGeometryApp::genSphere(std::vector<glm::vec4> points, int nm)
{
	return std::vector<glm::vec4>();
}

std::vector<glm::vec4> RenderingGeometryApp::rotatePoints(std::vector<glm::vec4> points, unsigned int nm)
{
	std::vector<glm::vec4> allPoints;
	for (int i = 0; i < nm + 1; i++)
	{
		float sphereSlice = (3.14 / nm);
		float theta = i * sphereSlice;

		for (int j = 0; j < points.size(); j++)
		{
			float newX = points[j].x;
			float newY = points[j].y * cos(theta) + points[j].z * sin(theta);
			float newZ = points[j].z = -sin(theta) + points[j].y * cos(theta);

			allPoints.push_back(glm::vec4(newX, newY, newZ, 1));
		}
	}
	return allPoints;
}

std::vector<unsigned int> RenderingGeometryApp::genIndices(int np, int nm)
{
	std::vector<unsigned int> indices;
	std::vector<unsigned int> bot_left;
	std::vector<unsigned int> bot_right;
	int i = 0;
	for (int j = 0; j < nm - 1; j++)
	{
		for (int y = 0; y < np; y++)
		{
			bot_left.push_back(i);
			bot_right.push_back(i + np);
			i++;
		}
	}
	for (int x = 1; x <= bot_left.size(); x++)
	{
		indices.push_back(bot_left[x-1]);
		indices.push_back(bot_right[x-1]);
		if (x % 3 == 0)
			indices.push_back(0xFFFF);
	}
	return indices;
}
