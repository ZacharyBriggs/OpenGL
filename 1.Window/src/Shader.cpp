#define GLM_FORCE_SWIZZLE
#include "Shader.h"
#include <cstdio>
#include "gl_core_4_4.h"



Shader::Shader()
{
	m_program = glCreateProgram();
}

Shader::~Shader()
{
}

void Shader::bind()
{
	glUseProgram(m_program);
}

void Shader::unbind()
{
	glUseProgram(0);
}

void Shader::load(const char * filename, unsigned int type, bool isFile)
{
	errno_t err;
	FILE *fp;
	err = fopen_s(&fp, filename, "r");
	char buf[500];

	while (std::fgets(buf, sizeof buf, fp))
	{
		if (type == 0)
			vsStr.append(buf);
		if (type == 1)
			fsStr.append(buf);
	}
	if (type == 0)
		vsSource = vsStr.c_str();
	if (type == 1)
		fsSource = fsStr.c_str();
}

bool Shader::attach()
{
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_vertexShader, 1, (const char**)&vsSource, 0);
	glCompileShader(m_vertexShader);
	glShaderSource(m_fragmentShader, 1, (const char**)&fsSource, 0);
	glCompileShader(m_fragmentShader);
	glAttachShader(m_program, m_vertexShader);
	glAttachShader(m_program, m_fragmentShader);
	glLinkProgram(m_program);

	int success = GL_FALSE;
	// check that it compiled and linked correctly
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE) {
		int infoLogLength = 0;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength + 1];
		glGetProgramInfoLog(m_program, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);
		delete[] infoLog;
	}
	return true;
}

void Shader::defaultLoad()
{
	vsSource = "#version 410\n \
                layout(location = 0) in vec4 Position; \
                layout(location = 1) in vec4 Color; \
                out vec4 vColor; \
                uniform mat4 ProjectionViewWorld; \
                void main() { vColor = Color; \
                gl_Position = ProjectionViewWorld * Position; }";

	fsSource = "#version 410\n \
                in vec4 vColor; \
                out vec4 FragColor; \
                void main() { FragColor = vColor; }";
}

unsigned int Shader::getUniform(const char *mvp)
{
	return glGetUniformLocation(m_program, mvp);;
}
