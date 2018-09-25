#define GLM_FORCE_SWIZZLE
#include "Shader.h"
#include "MeshRenderer.h"
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
	std::vector<Vertex> vertices = genCube(vertices);
	std::vector<unsigned int> indices = genCubeIndices();

	//gen sphere
	/*int nm = 5;
	int np = 4;
	std::vector<glm::vec4> points = genHalfCircle(np,5);
	std::vector<glm::vec4> spherePoints = genSphere(points, nm);
	std::vector<unsigned int> indices = genIndices(np, nm);
	std::vector<Vertex> vertices;
	for (glm::vec4 point : spherePoints)
	{
		vertices.push_back(Vertex(point, glm::vec4(1, 1, 1, 1)));
	}*/
	mesh->initialize(indices, vertices);
}
float rt = 0;

void RenderingGeometryApp::update(float dt)
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

std::vector<glm::vec4> RenderingGeometryApp::genHalfCircle(int np,int radius)
{
	std::vector<glm::vec4> points;

	for (float i = 0; i < np; i++)
	{
		float angle = glm::pi<float>() / ((float)np - 1);
		float theta = i * angle;

		points.push_back(glm::vec4(glm::cos(theta) * radius, glm::sin(theta) * radius, 0, 1));
	}
	return points;
}

std::vector<glm::vec4> RenderingGeometryApp::genSphere(std::vector<glm::vec4> points, unsigned int nm)
{
	std::vector<glm::vec4> allPoints;
	for (int i = 0; i < nm + 1; i++)
	{
		float sphereSlice = (glm::pi<float>()  * 2) / (float)nm;
		float theta = i * sphereSlice;

		for (int j = 0; j < points.size(); j++)
		{
			float newX = points[j].x;
			float newY = points[j].y * cos(theta) + points[j].z * -sin(theta);
			float newZ = points[j].z * cos(theta) + points[j].y * sin(theta);
			glm::vec4 point = glm::vec4(newX, newY, newZ, 1);
			allPoints.push_back(point);
		}
	}
	return allPoints;
}

std::vector<unsigned int> RenderingGeometryApp::genIndices(unsigned int np, unsigned int nm)
{
	std::vector<unsigned int> indices;

	unsigned int start;
	unsigned int bot_left;
	unsigned int bot_right;

	for (int y = 0; y < nm; y++)
	{
		start = y * np;

		for (int j = 0; j < np; j++)
		{
			bot_left = start + j;
			bot_right = bot_left + np;

			indices.push_back(bot_left);
			indices.push_back(bot_right);
		}
		indices.push_back(0xFFFF);
	}
	return indices;
}

std::vector<Vertex> RenderingGeometryApp::genPlane(int size)
{
	Vertex a = Vertex(glm::vec4(-size, size, 0, 1), glm::vec4(1, 0, 0, 1));
	Vertex b = Vertex(glm::vec4(size, size, 0, 1), glm::vec4(1, 0, 0, 1));
	Vertex c = Vertex(glm::vec4(size, -size, 0, 1), glm::vec4(1, 0, 0, 1));
	Vertex d = Vertex(glm::vec4(-size, -size, 0, 1), glm::vec4(1, 0, 0, 1));
	std::vector<Vertex> vertices = { a,b,c,d };
	return vertices;
}

std::vector<Vertex> RenderingGeometryApp::genCube(std::vector<Vertex> vertices)
{
	std::vector<Vertex> verts;
	//Front
	verts.push_back(Vertex(glm::vec4(0, 1, 1, 1),glm::vec4(1)));//0
	verts.push_back(Vertex(glm::vec4(1, 1, 1, 1), glm::vec4(1)));//1
	verts.push_back(Vertex(glm::vec4(1, 0, 1, 1), glm::vec4(1)));//2
	verts.push_back(Vertex(glm::vec4(0, 0, 1, 1), glm::vec4(1)));//3

	//Bot
	verts.push_back(Vertex(glm::vec4(0, 0, 0, 1), glm::vec4(1)));//4
	verts.push_back(Vertex(glm::vec4(1, 0, 0, 1), glm::vec4(1)));//5

	//Back
	verts.push_back(Vertex(glm::vec4(1, 1, 0, 1), glm::vec4(1)));//6
	verts.push_back(Vertex(glm::vec4(0, 1, 0, 1), glm::vec4(1)));//7

	//Top
	verts.push_back(Vertex(glm::vec4(0, 1, 1, 1), glm::vec4(1)));//8
	verts.push_back(Vertex(glm::vec4(1, 1, 1, 1), glm::vec4(1)));//9

	//Right
	verts.push_back(Vertex(glm::vec4(1, 1, 0, 1), glm::vec4(1)));//10
	verts.push_back(Vertex(glm::vec4(1, 0, 0, 1), glm::vec4(1)));//11

	//Left
	verts.push_back(Vertex(glm::vec4(0, 1, 0, 1), glm::vec4(1)));//12
	verts.push_back(Vertex(glm::vec4(0, 0, 0, 1), glm::vec4(1)));//13
	return verts;
}

std::vector<unsigned int> RenderingGeometryApp::genCubeIndices()
{
	std::vector<unsigned int> indices = 
	{	0,1,2,2,3,0,//front
		3,2,4,4,5,2,//Bot
		4,5,6,6,7,4,//Back
		6,7,8,8,9,6,//Top
		2,1,10,10,11,2,//Right
		0,3,12,12,13,0//Left
	};
	//for (int i = 0; i<np; i++)
	//{
	//	indices.push_back(i);
	//	/*if (i % 2 == 0 && i != 0)
	//	indices.push_back(i);*/
	//}
	//indices.push_back(0);
	return indices;
}