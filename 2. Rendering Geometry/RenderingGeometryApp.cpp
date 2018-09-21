#define GLM_FORCE_SWIZZLE
#include "Shader.h"
#include "MeshRenderer.h"
#include "Vertex.h"
#include "RenderingGeometryApp.h"
#include <glm/glm/ext.hpp>
#include "gl_core_4_4.h"



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
	defaultShader->defaultLoad();
	defaultShader->attach();
	std::vector<glm::vec4> points = genHalfCircle(10, 10);
	points = rotatePoints(points, 10);

	std::vector<unsigned int> indices;
	for(int i = 0;i < points.size();i++)
	{
		indices.push_back(i);
	}

	std::vector<Vertex> vertexs;
	for(glm::vec4 point : points)
	{
		vertexs.push_back(Vertex(point, glm::vec4(1, 1, 1, 1)));
	}
	mesh->initialize(indices, vertexs);
}

void RenderingGeometryApp::update(float dt)
{
	m_model = glm::mat4(1);
	glm::vec3 eye = glm::vec3(0, -10, 40);
	m_view = glm::lookAt(eye, m_model[3].xyz(), glm::vec3(0, 1, 0));
	m_projection = glm::perspective(glm::quarter_pi<float>(), 800 / (float)600, 0.1f, 1000.f);
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
		float sphereSlice = (3.14 / 2.0f);
		float theta = i * sphereSlice;

		for (int j = 0; j < points.size(); j++)
		{
			float newX = points[j].x;
			float newY = points[j].y * cos(theta) + points[j].y * sin(theta);
			float newZ = points[j].z = sin(theta)* - points[j].z * cos(theta);

			allPoints.push_back(glm::vec4(newX, newY, newZ, 1));
		}
	}
	return allPoints;
}
