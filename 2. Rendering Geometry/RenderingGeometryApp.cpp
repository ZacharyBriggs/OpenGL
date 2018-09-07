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
	glUseProgram(m_program);
	int handle = glGetUniformLocation(m_program,"ProjectionViewWorld");
	glm::mat4 mvp = m_projection*m_view*m_model;
	glUniformMatrix4fv(handle, 1, GL_FALSE, &mvp[0][0]);
	mesh->render();
	glUseProgram(0);
	/*glUseProgram(m_program);
	mvp = m_projection * m_view * m_model*glm::translate(m_model,glm::vec3(5,0,0));*/
}

void RenderingGeometryApp::shutdown()
{
}

